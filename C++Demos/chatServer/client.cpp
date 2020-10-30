#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")



/* 1 确定协议版本
 * 2 创建socket
 * 3 获取服务器协议簇
 * 4 连接
 * 5 通信
 * 6 断开
 * 7 清理协议版本信息
 */
int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2) {
		printf("协议版本不匹配: %d \n", GetLastError());
		getchar();
		return -1;
	}

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == client) {
		printf("创建socket失败: %d \n", GetLastError());
		WSACleanup();
		getchar();
		return -1;
	}

	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9565);

	int res = connect(client, (sockaddr*)&addr, sizeof(addr));
	if (SOCKET_ERROR == res) {
		printf("连接服务器失败: %d \n", GetLastError());
		closesocket(client);
		WSACleanup();
		getchar();
		return -1;
	}

	char buff[1024];
	while (1) {
		printf("我 >>> ");
		scanf("%s", buff);
		send(client, buff, strlen(buff), NULL);
	}

	closesocket(client);
	WSACleanup();

	getchar();

	return 0;
}