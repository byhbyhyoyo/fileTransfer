
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include "util.h"
#include <stdio.h>
//#include "strategy.h"
#include "config.h"
#include <cstring>
#include <string>
#include <thread>
#include <regex>
#include <filesystem>
#include <stdlib.h>
#include <Windows.h>
#include <io.h>

extern int state;

char* get_filename(char* p)
{
    char ch = '\\';
    char* q = strrchr(p, ch) + 1;

    return q;
}

const char* get_prompt_filename(char *prompt) {
    std::string prompt_string(prompt);
    std::smatch matches;
    const char* prompt_filename = NULL;
    if (std::regex_search(prompt_string, matches, FILENAME_PATTERN)) {
        if(matches.size() > 1){
            std::string matched_filename = matches[1];
            prompt_filename = matched_filename.c_str();
        }
    }
    return prompt_filename;
}

bool is_receive(SOCKET sock, char * file_full_path) {
    char flag[4];
    size_t str_len;
    char *filename = get_filename(file_full_path);
    size_t prompt_len = strlen(USERNAME) + strlen(SEND_PROMPT1) + strlen(filename) + strlen(SEND_PROMPT2);
    char* prompt = (char*)malloc(prompt_len);
    memset(prompt, '\0', prompt_len);

    strcat(prompt, USERNAME);
    strcat(prompt, SEND_PROMPT1);
    strcat(prompt, filename);
    strcat(prompt, SEND_PROMPT2);


    send(sock, prompt, strlen(prompt), 0);
    str_len = recv(sock, flag, sizeof(flag) - 1, 0);
    if (str_len <= 0) {
        printf("recv() error - is_receive()\n");
    }
    else {
        if (strcmp(flag, YES_FLAG) == 0) return true;
    }
    free(prompt);
    return false;
}
void send_file() {

    SOCKET send_sock;
    char flag[5];

    send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == INVALID_SOCKET) {
        printf("socket");
        return;
    }
    char addr[20];
    char full_path[100];

    struct sockaddr_in recv_addr;
    while (1) {
        //if (state == SEND_STATE) {
            
        memset(flag, '\0', sizeof(flag));
        scanf("%s", flag);
        if (strcmp(flag, SEND_FLAG) == 0) {
            printf("请输入你要连接的目的IP：");
            scanf("%s", addr);

            // 还需判断IP的有效性
            
            printf("请输入你要传输文件的绝对路径：");
            scanf("%s", full_path);
            // 需判断文件绝对路径的有效性
            if (_access(full_path, 0) == 0 && _access(full_path, 6) == 0) {
                memset(&recv_addr, 0, sizeof(recv_addr));
                recv_addr.sin_family = AF_INET;
                recv_addr.sin_addr.s_addr = inet_addr(addr);
                recv_addr.sin_port = htons(atoi(PORT));

                if (connect(send_sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) == -1) {
                    //char message[] = "connect() error";
                    //error_handling(message);
                    printf("connect() error\n");
                    continue;
                }
                char* file_content = get_file_content(full_path);
                char* file_name = get_filename(full_path);

                //printf("file_name : %s", file_name);
                //printf("strlen(file_name): %d", strlen(file_name));
                send(send_sock, file_name, strlen(file_name), 0);
                Sleep(3);

                send(send_sock, file_content, file_size, 0);
                printf("发送成功\n");
            }
            else if(_access(full_path, 0) != 0){
                printf("文件不存在\n");
            }
            else if (_access(full_path, 6) != 0) {
                printf("文件不可读\n");
            }

        }
        else {
            printf("输入错误，请重新输入");
        }



            //if (is_receive(send_sock, full_path)) {

            //}
            //else {
            //    printf("对方拒绝了你的文件传输请求");
            //}

        //    state = OTHER_STATE;   //涉及到对共享区的操作，应上锁
        //}
    }
}

void receive_file() {
    SOCKET recv_sock, send_sock;
    struct sockaddr_in send_addr;
    struct sockaddr_in recv_addr;
    int send_addr_len;
    int str_len;
    char file_content[10000];
    char prompt[100];
    char file_name[50];
    recv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // 注意此处与Linux不同
    if (recv_sock == INVALID_SOCKET)
    {
        printf("套接字创建失败！\n");
        return;
    }
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;           // 注意此处与Linux不同
    recv_addr.sin_addr.S_un.S_addr = INADDR_ANY;    // 注意此处与Linux不同
    recv_addr.sin_port = htons(atoi(PORT));

    // atoi(PORT)

    if (bind(recv_sock, (SOCKADDR*)&recv_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        printf("bind() error\n");
        return;
    }

    if (listen(recv_sock, 5) == SOCKET_ERROR) {
        printf("listen() error\n");
        return;
    }

    send_addr_len = sizeof(send_addr);
    while (1) {
        memset(file_content, '\0', sizeof(file_content));
        memset(file_name, '\0', sizeof(file_name));
        /*memset(prompt, '\0', sizeof(prompt));*/
        send_sock = accept(recv_sock, (struct sockaddr*)&send_addr, &send_addr_len);
        if (send_sock == INVALID_SOCKET) {
            printf("accept() error\n");
            return;
        }

        str_len = recv(send_sock, file_name, sizeof(file_name) - 1, 0);
        if (str_len <= 0) {
            printf("recv() error - prompt\n");
            return;
        }
        printf("file_name: %s", file_name);
        //printf("%s", prompt);

        //if (state == RECV_STATE) {
        //send(recv_sock, YES_FLAG, sizeof(YES_FLAG), 0);
        //const char* file_name = get_prompt_filename(prompt);
        Sleep(1);

        str_len = recv(send_sock, file_content, sizeof(file_content) - 1, 0);
        if (str_len <= 0) {
            printf("recv() error - file content\n");
            return;
        }
        char full_path[100] = "";
        strcat(full_path, RES_PATH);
        strcat(full_path, file_name);
        printf("full_path: %s\n", full_path);
        write_file(full_path, file_content, str_len);
        printf("接收文件成功，文件保存至：%s\n", full_path);
        printf("message from client : %s \n", file_content);
        // write(clnt_sock, message, sizeof(message));
        closesocket(send_sock);

        //    state = OTHER_STATE;
        //}
        //else if (state == NO_RECV_STATE) {
        //    send(recv_sock, NO_FLAG, sizeof(NO_FLAG), 0);
        //    state = OTHER_STATE;
        //}
    }
    // 关闭套接字
    closesocket(recv_sock);

}
char* get_file_content(char* full_path) {
    FILE* fp;

    char* tmp;

    fp = fopen(full_path, "r");
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    printf("文件字符数为 %d\n", file_size);
    tmp = (char*)malloc(file_size * sizeof(char));
    memset(tmp, '\0', file_size * sizeof(char));
    fseek(fp, 0, SEEK_SET);
    fread(tmp, sizeof(char), file_size, fp);
    printf("文件内容为：\n%s", tmp);
    fclose(fp);
    return tmp;
}

void write_file(char* full_path, char* file_content, int file_content_len) {
    FILE* fd;
    fd = fopen(full_path, "w");
    if (fd != NULL) {
        fwrite(file_content, sizeof(char), file_content_len, fd);
    }
    fclose(fd);
}
