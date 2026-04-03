#include "card_service.h"
#include "card_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lpCardNode cardList = NULL;

int initCardList() {
    cardList = (lpCardNode)malloc(sizeof(CardNode));
    cardList->next = NULL;
    return 1;
}

void clearCardList() {
    lpCardNode p = cardList->next, q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    cardList->next = NULL;
}

void releaseCardList() {
    clearCardList();
    free(cardList);
    cardList = NULL;
}

int reloadCardsFromFile() {
    clearCardList();
    int count = getCardFileCount(CARD_FILE);
    Card* arr = (Card*)malloc(count * sizeof(Card));
    int real = loadAllCardsFromFile(arr);

    for (int i = 0; i < real; i++) {
        lpCardNode node = (lpCardNode)malloc(sizeof(CardNode));
        node->data = arr[i];
        node->next = NULL;

        lpCardNode tail = cardList;
        while (tail->next) tail = tail->next;
        tail->next = node;
    }
    free(arr);
    return 1;
}

int addCard(Card card) {
    reloadCardsFromFile();

    lpCardNode p = cardList->next;
    while (p) {
        if (strcmp(p->data.card_id, card.card_id) == 0) {
            return -1;
        }
        p = p->next;
    }

    if (!saveCardToFile(&card)) {
        return -2;
    }
    return 0;
}

lpCardNode queryCard(const char* card_id) {
    reloadCardsFromFile();
    lpCardNode p = cardList->next;
    while (p) {
        if (strcmp(p->data.card_id, card_id) == 0 && p->data.is_deleted == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

Card* fuzzyQueryCards(const char* key, int* outCount) {
    reloadCardsFromFile();
    *outCount = 0;
    lpCardNode p = cardList->next;
    while (p) {
        if (strstr(p->data.card_id, key) != NULL && p->data.is_deleted == 0) (*outCount)++;
        p = p->next;
    }
    if (*outCount == 0) return NULL;
    Card* res = (Card*)malloc(*outCount * sizeof(Card));
    int idx = 0;
    p = cardList->next;
    while (p) {
        if (strstr(p->data.card_id, key) != NULL && p->data.is_deleted == 0) {
            res[idx++] = p->data;
        }
        p = p->next;
    }
    return res;
}
