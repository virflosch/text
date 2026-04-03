#ifndef CARD_FILE_H
#define CARD_FILE_H

#include "global.h"

#define CARD_FILE "./data/card.txt"

int saveCardToFile(const Card* card);
int getCardFileCount(const char* path);
int loadAllCardsFromFile(Card* outCards);
Card parseCardLine(char* buf);

#endif
