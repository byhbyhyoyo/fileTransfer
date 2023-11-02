//#include "strategy.h"
//#include "./config.h"
//#include <winsock2.h>
//#include <stdio.h>
//#include <string.h>
//int file_size;
//void LocalNetworkStrategy::transfer(void* sock_ptr) {
//    SOCKET sock = *(SOCKET*)sock_ptr;
//    char addr[20];
//    char port[10];
//    char full_path[100];
//
//    struct sockaddr_in serv_addr;
//    while (1) {
//        char flag[5];
//        printf("-------------若你需要传输文件，请输入%s, 并按回车--------------\n", SEND_FLAG);
//        scanf("%s", flag);
//        if (strcmp(flag, SEND_FLAG) == 0) {
//            printf("请输入你要连接的目的IP：");
//            scanf("%s", addr);
//
//            printf("请输入你要传输的文件绝对路径：");
//            scanf("%s", full_path);
//
//            memset(&serv_addr, 0, sizeof(serv_addr));
//            serv_addr.sin_family = AF_INET;
//            serv_addr.sin_addr.s_addr = inet_addr(addr);
//            serv_addr.sin_port = htons(atoi(PORT));
//            if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
//                char message[] = "connect() error";
//                error_handling(message);
//            }
//            char* file_content = get_file_content(full_path);
//            write(sock, file_content, file_size);
//
//
//        }
//        else {
//            printf("输入错误，请重新输入\n");
//            continue;
//        }
//    }
//}
//
//void LocalNetworkStrategy::receive(void* sock_ptr) {
//    SOCKET sock = *(SOCKET*)sock_ptr;
//    struct sockaddr_in addr;
//    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
//
//    memset(&addr, 0, sizeof(addr));
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    serv_addr.sin_port = htons(atoi(PORT));
//
//}
//
//
//
