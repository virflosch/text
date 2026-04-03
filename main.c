#include <stdio.h>
#include "tool.h"
#include "menu.h"
#include "card_service.h"

int main() {
    int choice = -1;

    // 初始化卡信息链表（程序启动时执行）
    if (initCardList() != 0) {
        printf("链表初始化失败，程序退出！\n");
        pauseProgram();
        return -1;
    }

    // 主菜单循环
    do {
        showMainMenu();
        printf("请选择菜单项编号(0~9)：");

        // 菜单选项输入校验（仅0~9）
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 9) {
            while (getchar() != '\n'); // 清空输入缓冲区
            printf("输入的菜单编号错误！请重新输入(0~9)：");
        }

        // 菜单功能分发
        switch (choice) {
        case 1: addCardUI(); break;          // 添加卡（链表版）
        case 2: queryCardUI(); break;        // 精确查询卡（链表版）
        case 3: fuzzyQueryCardUI(); break;   // 模糊查询卡（新增）
        case 4: printf("------上机功能待实现------\n"); break;
        case 5: printf("------下机功能待实现------\n"); break;
        case 6: printf("------充值功能待实现------\n"); break;
        case 7: printf("------退费功能待实现------\n"); break;
        case 8: printf("------查询统计功能待实现------\n"); break;
        case 9: printf("------注销卡功能待实现------\n"); break;
        case 0:
            printf("------退出系统，感谢使用！------\n");
            // 释放链表内存（防止内存泄漏）
            releaseCardList();
            break;
        }

        // 非退出选项，暂停后返回主菜单
        if (choice != 0) {
            pauseProgram();
        }
    } while (choice != 0);

    return 0;
}