#ifndef MY_CONFIG_H
#define MY_CONFIG_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <regex>
const static char RES_PATH[] = "C:\\Users\\Admin\\Desktop\\resource\\";
const static char PORT[] = "9006";
const static char SEND_FLAG[] = "send";
const static char YES_FLAG[] = "yes";
const static char NO_FLAG[] = "no";

const static char USERNAME[] = "Bao yang hao";
const static char SEND_PROMPT1[] = " send to you ";
const static char SEND_PROMPT2[] = ", do you want to receive？（please input yes or no）:";
static std::regex FILENAME_PATTERN("you (.*),");

const static int OTHER_STATE = 0;
const static int RECV_STATE = 1;
const static int NO_RECV_STATE = 2;
const static int SEND_STATE = 3;

const static int MAX_IP_ADDRESSES = 30; //最多支持同时向30个人传送文件
//const char IS_RECEIVE
// 公网服务器IP以及公网服务器端口号也可在此配置


#endif