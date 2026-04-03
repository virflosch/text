#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H

#include "global.h"
#include "model.h"

// 全局链表头结点（声明）
extern lpCardNode cardList;

// 链表初始化（创建头结点，数据区为空）
int initCardList();

// 释放链表内存（防止内存泄漏）
void releaseCardList();

// 添加卡到链表尾部（替换原数组添加逻辑）
int addCard(Card new_card);

// 精确查询：根据卡号查找（返回结点指针，NULL=未找到）
lpCardNode queryCard(const char* card_id);

// 模糊查询：根据关键字查找所有匹配卡（返回卡数组，pCount返回匹配数量）
Card* queryCards(const char* keyword, int* pCount);

#endif // CARD_SERVICE_Hf // CARD_SERVICE_HARD_SERVICE_H