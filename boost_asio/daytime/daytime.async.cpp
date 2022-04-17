/*************************************************************************
    > File Name: echo.async.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/


#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <ctime>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    using namespace std;  // For time_t, time and ctime;
    time_t now = time(nullptr);
    return ctime(&now);
}

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    typedef std::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context) {
        return pointer(new tcp_connection(io_context));
        // 不用以下形式提高效率，因为构造函数是private，tcp_server中建立新连接会失败
        // return std::make_shared<tcp_connection>(io_context);
    }

    tcp::socket& socket() { return socket_; }

    void start() {
        message_ = make_daytime_string();

        auto self = shared_from_this();
        boost::asio::async_write(
            socket_, boost::asio::buffer(message_),
            [self = std::move(self)](auto error, auto bytes_transferred) {
                self->handle_write(error, bytes_transferred);
            });
    }

private:
    tcp_connection(boost::asio::io_context& io_context) : socket_(io_context) {}

    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/) {}

    tcp::socket socket_;
    std::string message_;
};

class tcp_server {
public:
    tcp_server(boost::asio::io_context& io_context)
        : io_context_(io_context),
          acceptor_(io_context, tcp::endpoint(tcp::v4(), 13)) {
        start_accept();
    }

private:
    void start_accept() {
        tcp_connection::pointer new_connection =
            tcp_connection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(),
                               [this, new_connection](auto error) {
                                   this->handle_accept(new_connection, error);
                               });
    }

    void handle_accept(tcp_connection::pointer          new_connection,
                       const boost::system::error_code& error) {
        // 异步进行已建立连接start serve，同时继续监听，建立新的连接
        if (!error) {
            new_connection->start();
        }
        start_accept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor            acceptor_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        tcp_server              server(io_context);
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
