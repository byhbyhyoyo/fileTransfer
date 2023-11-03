#pragma once
#ifndef MY_UTIL_H
#define MY_UTIL_H
#include <winsock.h>
static int file_size;
char* get_file_content(char* full_path);
void write_file(char* full_path, char* file_content, int file_content_len);
char* get_filename(char* p);
const char* get_prompt_filename(char* prompt);
bool is_receive(SOCKET sock, char* file_full_path);
void send_file();
void receive_file();
char* get_file_content(char* full_path);
void write_file(char* full_path, char* file_content, int file_content_len);
void send_to_target(char* full_path, char* addr);
#endif