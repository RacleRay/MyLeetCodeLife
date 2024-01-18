#ifndef __MESSAGE__H__
#define __MESSAGE__H__

#include <stdint.h>

// 消息开始标记 uint32_t 全1
#define START_FLAG 0xFFFFFFFF
// 消息结束标记 uint32_t 全1最后一位为0
#define END_FLAG 0xFFFFFFFE

#pragma pack(push, 1)
struct COMMAND {
    unsigned char command_flag;   // 命令标志
    unsigned char response_flag;  // 响应标志
};

struct DATA {
    uint16_t data_length;   // 0-3长度不合法，4-65535长度也合法
    uint16_t data_flag;        
};

struct MCP_B {
    struct COMMAND command;
    struct DATA data;
    // char* value;      // 值
};
#pragma pack(pop)

// // 传输内容  65536 + 24 = 65560
// uint8_t buffer[65560] = {0};

// // 填充消息

// memset(buffer, START_FLAG, sizeof(START_FLAG));
// // 定义好 MCP_B 后
// memcpy(buffer + sizeof(START_FLAG), &MCP_B, sizeof(MCP_B));
// // 填充变长数据
// memcpy(buffer + sizeof(MCP_B) + sizeof(START_FLAG), value, MCP_B.data.data_length);
// // 填充结束标记
// memset(buffer + sizeof(MCP_B) + sizeof(START_FLAG) + MCP_B.data.data_length, END_FLAG, sizeof(END_FLAG));

// // 然后 socket 传输 buffer 就行



#endif  //!__MESSAGE__H__