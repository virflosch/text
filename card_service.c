#include "card_service.h"
#include "global.h"
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局变量：卡信息链表头结点
lpCardNode cardList = NULL;

// 初始化链表（创建空的头结点）
int initCardList() {
    // 分配头结点内存
    cardList = (lpCardNode)malloc(sizeof(CardNode));
    if (cardList == NULL) {
        return -1; // 内存分配失败
    }
    // 头结点数据区置空，指针置NULL
    memset(&cardList->data, 0, sizeof(Card));
    cardList->next = NULL;
    return 0; // 初始化成功
}

// 释放链表所有结点内存
void releaseCardList() {
    lpCardNode pTemp = NULL;
    lpCardNode pCurrent = cardList;

    // 遍历链表，逐个释放
    while (pCurrent != NULL) {
        pTemp = pCurrent;
        pCurrent = pCurrent->next;
        free(pTemp);
    }
    cardList = NULL; // 头结点置空
}

// 添加卡到链表尾部
int addCard(Card new_card) {
    // 1. 检查链表是否初始化
    if (cardList == NULL) {
        if (initCardList() != 0) {
            return -2; // 链表初始化失败
        }
    }

    // 2. 检查卡号是否重复（遍历链表）
    lpCardNode pCurrent = cardList->next;
    while (pCurrent != NULL) {
        if (strcmp(pCurrent->data.card_id, new_card.card_id) == 0) {
            return -1; // 卡号已存在
        }
        pCurrent = pCurrent->next;
    }

    // 3. 分配新结点内存
    lpCardNode pNewNode = (lpCardNode)malloc(sizeof(CardNode));
    if (pNewNode == NULL) {
        return -3; // 内存分配失败
    }

    // 4. 初始化新结点
    pNewNode->data = new_card;       // 复制卡信息
    pNewNode->data.status = CARD_OFFLINE; // 默认未上机
    pNewNode->data.total_used = 0.0f;
    pNewNode->data.use_count = 0;
    strcpy(pNewNode->data.last_use_time, "");
    pNewNode->next = NULL;           // 尾结点next置空

    // 5. 找到链表尾部，添加新结点
    pCurrent = cardList;
    while (pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNewNode;

    return 0; // 添加成功
}

// 精确查询：根据卡号查找
lpCardNode queryCard(const char* card_id) {
    // 检查链表是否初始化
    if (cardList == NULL) {
        return NULL;
    }

    // 遍历链表（跳过空的头结点）
    lpCardNode pCurrent = cardList->next;
    while (pCurrent != NULL) {
        if (strcmp(pCurrent->data.card_id, card_id) == 0) {
            return pCurrent; // 找到匹配结点
        }
        pCurrent = pCurrent->next;
    }

    return NULL; // 未找到
}

// 模糊查询：根据关键字查找所有匹配卡
Card* queryCards(const char* keyword, int* pCount) {
    *pCount = 0; // 初始化匹配数量
    Card* pResult = NULL; // 结果数组

    // 1. 检查链表是否初始化
    if (cardList == NULL) {
        return NULL;
    }

    // 2. 第一次遍历：统计匹配数量
    lpCardNode pCurrent = cardList->next;
    while (pCurrent != NULL) {
        // 使用strstr实现模糊匹配（卡号包含关键字）
        if (strstr(pCurrent->data.card_id, keyword) != NULL) {
            (*pCount)++;
        }
        pCurrent = pCurrent->next;
    }

    // 3. 无匹配结果，直接返回
    if (*pCount == 0) {
        return NULL;
    }

    // 4. 分配结果数组内存
    pResult = (Card*)malloc(sizeof(Card) * (*pCount));
    if (pResult == NULL) {
        *pCount = 0;
        return NULL;
    }

    // 5. 第二次遍历：保存匹配结果
    pCurrent = cardList->next;
    int index = 0;
    while (pCurrent != NULL) {
        if (strstr(pCurrent->data.card_id, keyword) != NULL) {
            pResult[index++] = pCurrent->data;
        }
        pCurrent = pCurrent->next;
    }

    return pResult; // 返回结果数组（需外部释放）
}