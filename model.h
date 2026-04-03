#ifndef MODEL_H
#define MODEL_H

#include "global.h"

typedef struct CardNode {
    Card data;
    struct CardNode* next;
} CardNode, * lpCardNode;

#endif
