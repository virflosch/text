#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H

#include "global.h"
#include "model.h"

extern lpCardNode cardList;

int initCardList();
void releaseCardList();
void clearCardList();
int reloadCardsFromFile();

int addCard(Card card);
lpCardNode queryCard(const char* card_id);
Card* fuzzyQueryCards(const char* key, int* outCount);

#endif
