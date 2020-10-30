#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define CLIENT_NUM   10
SOCKET clients[10];

void funcThread(int i);

/* 1 确定协议版本
 * 2 创建socket
 * 3 获取服务器协议簇
 * 4 绑定
 * 5 监听
 * 6 接受连接
 * 7 通信
 * 8 断开
 * 9 清理协议版本信息
 */
int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2) {
		printf("协议版本不匹配: %d \n", GetLastError());
		getchar();
		return -1;
	}

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == server) {
		printf("创建socket失败: %d \n", GetLastError());
		WSACleanup();
		getchar();
		return -1;
	}

	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9565);

	int res = bind(server, (sockaddr*)&addr, sizeof(addr));
	if (SOCKET_ERROR == res) {
		printf("绑定socket失败: %d \n", GetLastError());
		closesocket(server);
		WSACleanup();
		getchar();
		return -1;
	}

	res = listen(server, 10);
	if (SOCKET_ERROR == res) {
		printf("socket监听失败: %d \n", GetLastError());
		closesocket(server);
		WSACleanup();
		getchar();
		return -1;
	}

	SOCKADDR_IN cAddr = { 0 };
	int len = sizeof(cAddr);
	//SOCKET client = accept(server, (sockaddr*)&cAddr, &len);
	for (int i = 0; i < CLIENT_NUM; ++i) {
		clients[i] = accept(server, (sockaddr*)&cAddr, &len);
		if (SOCKET_ERROR == clients[i]) {
			printf("接受客户端失败: %d \n", GetLastError());
			closesocket(server);
			WSACleanup();
			getchar();
			return -1;
		}
		printf("客户端%d连接成功: %s \n", i+1, inet_ntoa(cAddr.sin_addr));

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)funcThread, (void*)i, NULL, NULL);
	}

	

	closesocket(server);
	WSACleanup();
	getchar();
	return 0;
}


void funcThread(int i) {
	char buff[1024];
	while (1) {
		int res = recv(clients[i], buff, 1023, NULL);
		if (res > 0) {
			buff[res] = 0; // \0
			printf("客户端%d消息 >>> %s \n", i+1, buff);
		}
	}
};