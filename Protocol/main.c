#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "message.h"

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // 初始化服务器地址结构
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // 绑定套接字到指定地址和端口
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    // 监听连接请求
    listen(sockfd, 1);
    printf("等待客户端连接...\n");

    clilen = sizeof(cli_addr);

    // 接受客户端连接
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    // =====================================================
    // MCP_A 通信过程
    // ...
    // =====================================================
    

    // 与客户端通信
    while (1) {
        // 从客户端接收数据
        memset(buffer, 0, BUFFER_SIZE);
        n = read(newsockfd, buffer, BUFFER_SIZE - 1);
        if (n < 0) {
            perror("Error reading from socket");
            exit(1);
        }

        // 打印接收到的消息
        printf("接收到的消息: %s\n", buffer);

        // ======================================================================
        struct MCP_B message;
        message.command.command_flag = 0x01;
        message.command.response_flag = 0x02;

        message.data.data_length = 1024;
        message.data.data_flag = 0x03;

        char data[1024];
        memset(data, 1, 1024);

        // 发送响应给客户端
        uint64_t start_flag = START_FLAG;
        uint64_t end_flag = END_FLAG;

        char *buf = malloc(message.data.data_length + 48);
        memcpy(buf, &start_flag, sizeof(start_flag));
        memcpy(buf + sizeof(start_flag), &message, sizeof(message));
        memcpy(buf + sizeof(start_flag) + sizeof(message), data, message.data.data_length);
        memcpy(buf + sizeof(start_flag) + sizeof(message) + message.data.data_length, &end_flag, sizeof(end_flag));

        n = write(newsockfd, buf, sizeof(message));
        if (n < 0) {
            perror("Error writing to socket");
            exit(1);
        }
    }

    // 关闭套接字
    close(newsockfd);
    close(sockfd);

    return 0;
}