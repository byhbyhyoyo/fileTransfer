#include "util.h"
#include <stdio.h>
#include <thread>

// Ҫ��������IP�ţ���������飩���˿ںŹ̶�  
// 
int main() {

    WSADATA wsa;
    // LocalNetworkStrategy* locals = new LocalNetworkStrategy();
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup");
        return 0;
    }
    else {
        printf("��ʼ���׽��ֿ�ɹ�");
    }

    // ���������ж���һ��һ����һ�Զ�

    // �ж��Ǿ����� ���� ����
    std::thread send_thread(send_file);
    std::thread recv_thread(receive_file);
    send_thread.join();
    recv_thread.join();


    // �ж��Ƿ�Ҫ���ͣ�Ҫ���͵Ļ��������̵߳���transfer����

    WSACleanup();
    return 0;
}

