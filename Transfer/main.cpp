#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "util.h"
#include "config.h"
#include <stdio.h>
#include <thread>

// 要求输入是IP号（可输入多组），端口号固定  
// 
//int state = OTHER_STATE;


int main() {

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup");
        return 0;
    }
    printf("-------------你已经成功上线，你的用户名是%s--------------\n",USERNAME);
    printf("-------------若你需要传输文件，请输入%s, 并按回车--------------\n", SEND_FLAG);
    char flag[5];
    memset(flag, '\0', sizeof(flag));

    std::thread send_thread(send_file);
    std::thread recv_thread(receive_file);
    //while (scanf("%s", flag) != EOF) {
    //    if (strcmp(flag, SEND_FLAG) == 0) {
    //        state = SEND_STATE;
    //    }
    //    else if(strcmp(flag, YES_FLAG) == 0){
    //        state = RECV_STATE;
    //    }
    //    else if(strcmp(flag, NO_FLAG) == 0){
    //        state = NO_RECV_STATE;
    //    }
    //    else {
    //        state = OTHER_STATE;
    //        printf("输入错误，请重新输入\n");
    //    }
    //    Sleep(20);
    //}
    send_thread.join();
    recv_thread.join();


    // 判断是否要发送，要发送的话，启用线程调用transfer函数

    WSACleanup();
    return 0;
}

