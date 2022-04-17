/*************************************************************************
    > File Name: server.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/


#include "message.h"
#include "jsonser.h"
#include "serialization.h"
#include "Protocal.pb.h"

#include <boost/asio.hpp>

#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>

#include <cstdlib>

using boost::asio::ip::tcp;

using chat_message_queue  = std::deque<chat_message>;
using chat_message_queue2 = std::list<chat_message>;

class chat_session;
using chat_session_ptr = std::shared_ptr<chat_session>;

//----------------------------------------------------------------------

class chat_room {
public:
    void join(chat_session_ptr);
    void leave(chat_session_ptr);
    void deliver(const chat_message&);

private:
    std::set<chat_session_ptr> participants_;
    enum { max_recent_msgs = 100 };
    chat_message_queue recent_msgs_;
};

//----------------------------------------------------------------------

class chat_session : public std::enable_shared_from_this<chat_session> {
public:
    chat_session(tcp::socket socket, chat_room& room)
        : socket_(std::move(socket)), room_(room) {}

    void start() {
        room_.join(shared_from_this());
        do_read_header();
    }

    void deliver(const chat_message& msg) {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress) {
            do_write();
        }
    }

private:
    void do_read_header() {
        auto self(shared_from_this());
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(read_msg_.data(), chat_message::header_length),
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec && read_msg_.decode_header()) {
                    do_read_body();
                }
                else {
                    std::cout << "Player leave the room\n";
                    room_.leave(shared_from_this());
                }
            });
    }

    void do_read_body() {
        auto self(shared_from_this());
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    handleMessage();
                    do_read_header();
                }
                else {
                    room_.leave(shared_from_this());
                }
            });
    }

    template <typename T> T toObject() {
        T obj;
        std::stringstream ss(std::string(
            read_msg_.body(), read_msg_.body() + read_msg_.body_length()));
        boost::archive::text_iarchive oa(ss);
        oa & obj;
        return obj;
    }

    ptree toPtree() {
        ptree obj;
        std::stringstream ss(
            std::string(read_msg_.body(), read_msg_.body() + read_msg_.body_length()));
        boost::property_tree::read_json(ss, obj);
        return obj;
    }

    bool fillProtobuf(::google::protobuf::Message* msg) {
        std::string ss(read_msg_.body(), read_msg_.body() + read_msg_.body_length());
        auto ok = msg->ParseFromString(ss);
        return ok;
    }

    void handleMessage() {
        if (read_msg_.type() == MT_BIND_NAME) {
#ifdef _ARCHIVE
            auto bindName = toObject<SBindName>();
            m_name        = bindName.bindName();
#endif
#ifdef _JSON
            auto nameTree = toPtree();
            m_name = nameTree.get<std::string>("name");
#endif
#ifdef _PROTO
            PBindName bindName;
            if(fillProtobuf(&bindName))
                m_name = bindName.name();
#endif
        }
        else if (read_msg_.type() == MT_CHAT_INFO) {
            chat_message msg;
#ifdef _ARCHIVE
            auto chat  = toObject<SChatInfo>();
            auto rinfo = buildRoomInfo();
            m_chatInformation = chat.chatInformation();
            msg.setMessage(MT_ROOM_INFO, rinfo);
#endif
#ifdef _JSON
            auto chat = toPtree();
            m_chatInformation = chat.get<std::string>("information");
            auto rinfo = buildRoomInfo();
            msg.setMessage(MT_ROOM_INFO, rinfo);
#endif
#ifdef _PROTO
            PChat chat;
            if(!fillProtobuf(&chat)) return;
            m_chatInformation = chat.information();
            auto rinfo = buildRoomInfo();
            msg.setMessage(MT_ROOM_INFO, rinfo);
#endif
            room_.deliver(msg);
        }
        else {
            // not valid msg do nothing
        }
    }

    void do_write() {
        auto self(shared_from_this());
        boost::asio::async_write(
            socket_,
            boost::asio::buffer(write_msgs_.front().data(),
                                write_msgs_.front().length()),
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    write_msgs_.pop_front();
                    if (!write_msgs_.empty()) {
                        do_write();
                    }
                }
                else {
                    room_.leave(shared_from_this());
                }
            });
    }

    std::string buildRoomInfo() const {
        std::string ret;
#ifdef _ARCHIVE
        SRoomInfo                     roomInfo(m_name, m_chatInformation);
        std::stringstream             ss;
        boost::archive::text_oarchive oa(ss);
        oa & roomInfo;
        ret = ss.str();
#endif
#ifdef _JSON
        ptree tree;
        tree.put("name", m_name);
        tree.put("information", m_chatInformation);
        ret = ptreeToJsonString(tree);
#endif
#ifdef _PROTO
        PRoomInformation roomInfo;
        roomInfo.set_name(m_name);
        roomInfo.set_information(m_chatInformation);
        auto ok = roomInfo.SerializeToString(&ret);
        assert(ok);
#endif
        return ret;
    }

    tcp::socket        socket_;
    chat_room&         room_;
    chat_message       read_msg_;
    chat_message_queue write_msgs_;
    std::string        m_name;
    std::string        m_chatInformation;
};


void chat_room::join(chat_session_ptr participant) {
    participants_.insert(participant);
    for (const auto& msg : recent_msgs_)
        participant->deliver(msg);
}

void chat_room::leave(chat_session_ptr participant) {
    participants_.erase(participant);
}

void chat_room::deliver(const chat_message& msg) {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();

    for (auto& participant : participants_)
        participant->deliver(msg);
}

//----------------------------------------------------------------------

class chat_server {
public:
    chat_server(boost::asio::io_service& io_service,
                const tcp::endpoint&     endpoint)
        : acceptor_(io_service, endpoint), socket_(io_service) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                auto session =
                    std::make_shared<chat_session>(std::move(socket_), room_);
                session->start();
            }

            do_accept();
        });
    }

    tcp::acceptor acceptor_;
    tcp::socket   socket_;
    chat_room     room_;
};

//----------------------------------------------------------------------

int main(int argc, char* argv[]) {
    try {
#ifdef _PROTO
        GOOGLE_PROTOBUF_VERIFY_VERSION;
#endif
        if (argc < 2) {
            std::cerr << "Usage: chat_server <port> [<port> ...]\n";
            return 1;
        }

        boost::asio::io_service io_service;

        std::list<chat_server> servers;
        for (int i = 1; i < argc; ++i) {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
        }

        io_service.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
#ifdef _PROTO
    google::protobuf::ShutdownProtobufLibrary();
#endif

    return 0;
}
