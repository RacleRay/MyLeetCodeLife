/*************************************************************************
    > File Name: header.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "header.h"
#include "jsonser.h"
#include "serialization.h"
#include "Protocal.pb.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

// T class deals with seriliazation
template <typename T> std::string seriliaze(const T& obj) {
    std::stringstream             ss;
    boost::archive::text_oarchive oa(ss);
    oa & obj;
    return ss.str();
}

/* boost cpp class serialization for message communicate.
 * */
bool parseMessageArchive(const std::string& input, int* type,
                         std::string& outbuffer) {
    auto pos = input.find_first_of(" ");
    if (pos == std::string::npos) return false;
    if (pos == 0) return false;

    auto command = input.substr(0, pos);
    if (command == "BindName") {
        // we try to bind name
        std::string name = input.substr(pos + 1);
        if (name.size() > 32) return false;
        if (type) *type = MT_BIND_NAME;
        outbuffer = seriliaze(SBindName(std::move(name)));
        return true;
    }
    else if (command == "Chat") {
        // we try to chat
        std::string chat = input.substr(pos + 1);
        if (chat.size() > 256) return false;
        outbuffer = seriliaze(SChatInfo(std::move(chat)));
        if (type) *type = MT_CHAT_INFO;
        return true;
    }
    return false;
}

// c struct message to communicate
bool parseMessageC(const std::string& input, int* type,
                   std::string& outbuffer) {
    auto pos = input.find_first_of(" ");
    if (pos == std::string::npos) return false;
    if (pos == 0) return false;

    auto command = input.substr(0, pos);
    if (command == "BindName") {
        // we try to bind name
        std::string name = input.substr(pos + 1);
        if (name.size() > 32) return false;
        if (type) *type = MT_BIND_NAME;
        BindName bindInfo;
        bindInfo.nameLen = name.size();
        std::memcpy(&(bindInfo.name), name.data(), name.size());
        auto buffer = reinterpret_cast<const char*>(&bindInfo);
        outbuffer.assign(buffer, buffer + sizeof(bindInfo));
        return true;
    }
    else if (command == "Chat") {
        // we try to chat
        std::string chat = input.substr(pos + 1);
        if (chat.size() > 256) return false;
        ChatInformation info;
        info.infoLen = chat.size();
        std::memcpy(&(info.information), chat.data(), chat.size());
        auto buffer = reinterpret_cast<const char*>(&info);
        outbuffer.assign(buffer, buffer + sizeof(info));
        if (type) *type = MT_CHAT_INFO;
        return true;
    }
    return false;
}

bool parseMessageJson(const std::string& input, int* type,
                      std::string& outbuffer) {
    auto pos = input.find_first_of(" ");
    if (pos == std::string::npos) return false;
    if (pos == 0) return false;

    auto command = input.substr(0, pos);
    if (command == "BindName") {
        // we try to bind name
        std::string name = input.substr(pos + 1);
        if (name.size() > 32) return false;
        if (type) *type = MT_BIND_NAME;
        ptree tree;
        tree.put("name", name);
        outbuffer = ptreeToJsonString(tree);
        // outbuffer = seriliaze(SBindName(std::move(name)));
        return true;
    }
    else if (command == "Chat") {
        // we try to chat
        std::string chat = input.substr(pos + 1);
        if (chat.size() > 256) return false;
        ptree tree;
        tree.put("information", chat);
        outbuffer = ptreeToJsonString(tree);
        // outbuffer = seriliaze(SChatInfo(std::move(chat)));
        if (type) *type = MT_CHAT_INFO;
        return true;
    }
    return false;
}

bool parseMessageProto(const std::string& input, int* type, 
                       std::string& outbuffer) {
    auto pos = input.find_first_of(" ");
    if (pos == std::string::npos) return false;
    if (pos == 0) return false;

    auto command = input.substr(0, pos);
    if (command == "BindName") {
        // we try to bind name
        std::string name = input.substr(pos + 1);
        if (name.size() > 32) return false;
        if (type) *type = MT_BIND_NAME;
        PBindName bindName;
        bindName.set_name(name);
        auto ok = bindName.SerializeToString(&outbuffer);
        return ok;
    }
    else if (command == "Chat") {
        // we try to chat
        std::string chat = input.substr(pos + 1);
        if (chat.size() > 256) return false;
        PChat pchat;
        pchat.set_information(chat);
        auto ok = pchat.SerializeToString(&outbuffer);
        if (type) *type = MT_CHAT_INFO;
        return ok;
    }
    return false;
}
