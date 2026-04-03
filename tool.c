#include "tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 清屏（Windows/Linux兼容）
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 暂停程序
void pauseProgram() {
#ifdef _WIN32
    system("pause");
#else
    printf("按任意键继续...");
    getchar();
#endif
}

// 获取当前时间（格式：2026-03-13 16:30）
void getCurrentTime(char* time_str) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(time_str, 20, "%Y-%m-%d %H:%M", tm_info);
}

// 输入卡号（校验1~18位）
void inputCardId(char* card_id) {
    while (1) {
        printf("请输入查询的卡号(长度为1~18)：");
        scanf("%s", card_id);
        if (strlen(card_id) >= 1 && strlen(card_id) <= CARD_ID_LEN) {
            break;
        }
        printf("卡号长度必须在1~18之间！\n");
    }
}

// 输入密码（校验1~8位）
void inputPassword(char* pwd) {
    while (1) {
        printf("请输入密码(长度为1~8)：");
        scanf("%s", pwd);
        if (strlen(pwd) >= 1 && strlen(pwd) <= PWD_LEN) {
            break;
        }
        printf("密码长度必须在1~8之间！\n");
    }
}