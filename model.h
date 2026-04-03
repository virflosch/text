#ifndef MODEL_H
#define MODEL_H

#include "global.h"

// 链表结点结构体
typedef struct CardNode {
    Card data;               // 数据区：卡信息
    struct CardNode* next;   // 指针区：指向下一个结点
} CardNode, * lpCardNode;

#endif // MODEL_H