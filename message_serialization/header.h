/*************************************************************************
    > File Name: header.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _HEADER_H
#define _HEADER_H

#include <string>
struct Header {
    int bodySize;
    int type;
};

enum MessageType {
    MT_BIND_NAME = 1,
    MT_CHAT_INFO = 2,
    MT_ROOM_INFO = 3,
};

// client send
struct BindName {
    char name[32];
    int  nameLen;
};

// client send
struct ChatInformation {
    char information[256];
    int  infoLen;
};


// serversend
struct RoomInformation {
    BindName        name;
    ChatInformation chat;
};

bool parseMessageC(const std::string& input, int* type, std::string& outbuffer);
bool parseMessageArchive(const std::string& input, int* type, std::string& outbuffer);
bool parseMessageJson(const std::string& input, int * type, std::string& outbuffer);
bool parseMessageProto(const std::string& input, int * type, std::string& outbuffer);

#endif
