#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  // 引入静态库


int merror(int redata, int error, char* showinfo) {
	if (redata == error) {
		perror(showinfo);
		getchar();
		return -1;
	}
	return 0;
}


void sendhtml(SOCKET s, char* filename);


int main() {
	printf("Web服务器启动... \n");
	WSADATA wsdata;
	int isok = WSAStartup(MAKEWORD(2, 2), &wsdata);  // socket版本
	merror(isok, WSAEINVAL, "申请socket失败 \n");

	// AF_INET: 协议族，决定地址类型
	// SOCK_STREAM: 传输类型
	// IPPROTO_TCP：传输协议
	SOCKET server=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	merror(server, INVALID_SOCKET, "创建socket失败 \n");

	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(80);  // 网络大端存储，pc上小端
	seraddr.sin_addr.s_addr = INADDR_ANY;  //监听任意地址
	
	isok = bind(server, &seraddr, sizeof(seraddr));
	merror(isok, SOCKET_ERROR, "绑定失败 \n");

	isok = listen(server, 5);
	merror(isok, SOCKET_ERROR, "监听失败 \n");

	struct sockaddr_in claddr;
	int cllen = sizeof(claddr);
	while (1) {
		SOCKET client = accept(server, &claddr, &cllen);
		merror(client, INVALID_SOCKET, "连接失败 \n");

		char revdata[1024] = "";
		recv(client, revdata, 1024, 0);
		printf("%s 共接受到%d字节数据 \n", revdata, strlen(revdata));

		//char senddata[1024] = "已收到一条信息 \n";
		//send(client, senddata, 20, 0);

		char* filename = "index.html";
		sendhtml(client, filename);

		closesocket(client);
	}

	closesocket(server);
	WSACleanup();

	getchar();
	return 0;
}


void sendhtml(SOCKET s, char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("文件打开失败 \n");
		return;
	}
	char temp[1024] = "";
	do {
		fgets(temp, 1024, file);
		send(s, temp, strlen(temp), 0);
	} while (!feof(file));
}