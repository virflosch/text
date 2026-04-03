#include "menu.h"
#include "tool.h"
#include "card_service.h"
#include "model.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 显示主菜单（不变，仅后续main.c新增选项）
void showMainMenu() {
    clearScreen();
    printf("--------------------菜单--------------------\n");
    printf("1.添加卡\n");
    printf("2.精确查询卡\n");
    printf("3.模糊查询卡\n"); // 新增选项
    printf("4.上机\n");
    printf("5.下机\n");
    printf("6.充值\n");
    printf("7.退费\n");
    printf("8.查询统计\n");
    printf("9.注销卡\n");
    printf("0.退出\n");
    printf("-------------------------------------------\n");
}

// 添加卡界面（仅适配链表，逻辑不变）
void addCardUI() {
    clearScreen();
    printf("--------添加卡--------\n");
    Card new_card;

    // 输入卡号（带长度校验）
    printf("请输入卡号(长度为1~18)：");
    scanf("%s", new_card.card_id);
    while (strlen(new_card.card_id) < 1 || strlen(new_card.card_id) > CARD_ID_LEN) {
        printf("卡号长度非法！请重新输入：");
        scanf("%s", new_card.card_id);
    }

    // 输入密码
    inputPassword(new_card.password);

    // 输入开卡金额（非负校验）
    printf("请输入开卡金额(RMB)：");
    scanf("%f", &new_card.balance);
    while (new_card.balance < 0) {
        printf("金额不能为负！请重新输入：");
        scanf("%f", &new_card.balance);
    }

    // 调用链表版添加逻辑
    int res = addCard(new_card);
    if (res == 0) {
        printf("--------添加的卡信息如下--------\n");
        printf("卡号\t密码\t状态\t开卡金额\n");
        printf("%s\t%s\t%d\t%.1f\n",
            new_card.card_id, new_card.password, new_card.status, new_card.balance);
    }
    else if (res == -1) {
        printf("添加失败！卡号 %s 已存在。\n", new_card.card_id);
    }
    else if (res == -2) {
        printf("添加失败！链表初始化失败。\n");
    }
    else if (res == -3) {
        printf("添加失败！内存分配失败。\n");
    }
}

// 精确查询卡界面（适配链表）
void queryCardUI() {
    clearScreen();
    printf("--------精确查询卡--------\n");
    char card_id[CARD_ID_LEN + 1];
    inputCardId(card_id);

    // 调用链表版精确查询
    lpCardNode pNode = queryCard(card_id);
    if (pNode != NULL) {
        printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
        const char* status_str = (pNode->data.status == CARD_OFFLINE) ? "未上机" : "已上机";
        printf("%s\t%s\t%.0f\t%.0f\t\t%d\t\t%s\n",
            pNode->data.card_id, status_str, pNode->data.balance,
            pNode->data.total_used, pNode->data.use_count, pNode->data.last_use_time);
    }
    else {
        printf("没有找到卡号为 %s 的卡信息！\n", card_id);
    }
}

// 模糊查询卡界面（新增核心功能）
void fuzzyQueryCardUI() {
    clearScreen();
    printf("--------模糊查询卡--------\n");
    char keyword[CARD_ID_LEN + 1];
    printf("请输入查询关键字（卡号包含该关键字）：");
    scanf("%s", keyword);

    int matchCount = 0;
    // 调用模糊查询函数
    Card* pResult = queryCards(keyword, &matchCount);

    if (matchCount == 0 || pResult == NULL) {
        printf("未找到包含关键字「%s」的卡信息！\n", keyword);
        return;
    }

    // 以列表格式显示所有匹配结果
    printf("\n--------查询结果（共%d条）--------\n", matchCount);
    printf("序号\t卡号\t\t状态\t余额\t累计使用\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < matchCount; i++) {
        const char* status_str = (pResult[i].status == CARD_OFFLINE) ? "未上机" : "已上机";
        // 格式化输出，适配不同长度卡号
        printf("%d\t%s\t\t%s\t%.0f\t%.0f\n",
            i + 1, pResult[i].card_id, status_str,
            pResult[i].balance, pResult[i].total_used);
    }

    // 释放模糊查询的结果数组内存
    free(pResult);
}