#ifndef TOOL_H
#define TOOL_H

#include "global.h"
#include <time.h>

// 清屏函数
void clearScreen();

// 暂停函数（等待按键）
void pauseProgram();

// 获取当前时间字符串（输出到time_str）
void getCurrentTime(char* time_str);

// 输入卡号（带长度校验）
void inputCardId(char* card_id);

// 输入密码（带长度校验）
void inputPassword(char* pwd);

#endif // TOOL_H