////server.cpp
//#include<iostream>
//#include<winsock.h>   // windows平台的网络库头文件
//#pragma comment(lib,"ws2_32.lib")   // 库文件
//using namespace std;
//
//#define PORT 5050
//#define BUFSIZ 512
//
//void initialization() {
//	//初始化套接字库
//	// WSA  windows socket async  windows异步套接字     WSAStartup启动套接字
//	// parm1:请求的socket版本 2.2 2.1 1.0     parm2:传出参数    参数形式：WORD  WSADATA
//	WORD w_req = MAKEWORD(2, 2);//版本号  
//	WSADATA wsadata;
//	// 成功：WSAStartup函数返回零
//	if (WSAStartup(w_req, &wsadata) != 0) {
//		cout << "初始化套接字库失败！" << endl;
//	}
//	else {
//		cout << "初始化套接字库成功！" << endl;
//	}
//}
//
//SOCKET createServeSocket(const char* ip)
//{
//	//1.创建空的Socket					
//		//parm1:af 地址协议族 ipv4 ipv6
//		//parm2:type 传输协议类型 流式套接字(SOCK_STREAM) 数据报
//		//parm3：protocl 使用具体的某个传输协议
//	SOCKET s_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (s_server == INVALID_SOCKET)
//	{
//		cout << "套接字创建失败！" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "套接字创建成功！" << endl;
//	}
//	//2.给socket绑定ip地址和端口号
//	struct sockaddr_in server_addr;   // sockaddr_in, sockaddr  老版本和新版的区别
//	server_addr.sin_family = AF_INET;  // 和创建socket时必须一样
//	server_addr.sin_port = htons(PORT);       // 端口号  大端（高位）存储(本地)和小端（低位）存储(网络），两个存储顺序是反着的  htons 将本地字节序转为网络字节序
//	server_addr.sin_addr.S_un.S_addr = inet_addr(ip); //inet_addr将点分十进制的ip地址转为二进制
//	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
//		cout << "套接字绑定失败！" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "套接字绑定成功！" << endl;
//	}
//
//	//3.设置套接字为监听状态  SOMAXCONN 监听的端口数 右键转到定义为5
//	if (listen(s_server, SOMAXCONN) < 0) {
//		cout << "设置监听状态失败！" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "设置监听状态成功！" << endl;
//	}
//	return s_server;
//}
//
//int main() {
//	//定义发送缓冲区和接受缓冲区长度
//	char send_buf[BUFSIZ];
//	char recv_buf[BUFSIZ];
//	//定义服务端套接字，接受请求套接字
//	SOCKET s_server;
//	SOCKET s_accept;
//
//	initialization(); // 初始化启动套接字
//	s_server = createServeSocket("127.0.0.1");
//	cout << "wait client connect..." << endl;
//	// 如果有客户端请求连接
//	s_accept = accept(s_server, NULL, NULL);
//	if (s_accept == INVALID_SOCKET) {
//		cout << "连接失败！" << endl;
//		WSACleanup();
//		return 0;
//	}
//	// 可以和客户端进行通信了
//	while (true) {
//		// recv从指定的socket接受消息
//		if (recv(s_accept, recv_buf, BUFSIZ, 0) > 0) {
//			cout << "客户端信息:" << recv_buf << endl;
//		}
//		else {
//			cout << "接受失败！" << endl;
//			break;
//		}
//		cout << "请输入回复信息:";
//		cin >> send_buf;
//		if (send(s_accept, send_buf, BUFSIZ, 0) < 0) {
//			cout << "发送失败！" << endl;
//			break;
//		}
//	}
//	//关闭套接字
//	closesocket(s_server);
//	closesocket(s_accept);
//	//释放DLL资源
//	WSACleanup();
//	return 0;
//}