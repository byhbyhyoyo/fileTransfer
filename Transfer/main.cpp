#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "util.h"
#include "config.h"
#include <stdio.h>
#include <thread>

// Ҫ��������IP�ţ���������飩���˿ںŹ̶�  
// 
//int state = OTHER_STATE;


int main() {

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup");
        return 0;
    }
    printf("-------------���Ѿ��ɹ����ߣ�����û�����%s--------------\n",USERNAME);
    printf("-------------������Ҫ�����ļ���������%s, �����س�--------------\n", SEND_FLAG);
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
    //        printf("�����������������\n");
    //    }
    //    Sleep(20);
    //}
    send_thread.join();
    recv_thread.join();


    // �ж��Ƿ�Ҫ���ͣ�Ҫ���͵Ļ��������̵߳���transfer����

    WSACleanup();
    return 0;
}

