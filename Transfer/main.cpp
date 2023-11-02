#include "util.h"
#include <stdio.h>
#include <thread>

// 要求输入是IP号（可输入多组），端口号固定  
// 
int main() {

    WSADATA wsa;
    // LocalNetworkStrategy* locals = new LocalNetworkStrategy();
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup");
        return 0;
    }
    else {
        printf("初始化套接字库成功");
    }

    // 根据输入判断是一对一还是一对多

    // 判断是局域网 还是 公网
    std::thread send_thread(send_file);
    std::thread recv_thread(receive_file);
    send_thread.join();
    recv_thread.join();


    // 判断是否要发送，要发送的话，启用线程调用transfer函数

    WSACleanup();
    return 0;
}

