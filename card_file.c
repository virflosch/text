#include "card_file.h"
#include "tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void createDataDir() {
    system("if not exist data mkdir data");
}

int saveCardToFile(const Card* card) {
    createDataDir();
    FILE* fp = fopen(CARD_FILE, "a+");
    if (!fp) return 0;

    char createStr[TIME_LEN] = { 0 };
    char expireStr[TIME_LEN] = { 0 };
    strftime(createStr, TIME_LEN, "%Y-%m-%d %H:%M", localtime(&card->create_time));
    strftime(expireStr, TIME_LEN, "%Y-%m-%d %H:%M", localtime(&card->expire_time));

    fprintf(fp, "%s##%s##%d##%s##%s##%.2f##%s##%d##%.2f##%d\n",
        card->card_id,
        card->password,
        card->status,
        createStr,
        expireStr,
        card->total_used,
        card->last_use_time,
        card->use_count,
        card->balance,
        card->is_deleted);
    fclose(fp);
    return 1;
}

int getCardFileCount(const char* path) {
    FILE* fp = fopen(path, "r");
    if (!fp) return 0;
    char buf[512];
    int cnt = 0;
    while (fgets(buf, 512, fp)) cnt++;
    fclose(fp);
    return cnt;
}

Card parseCardLine(char* buf) {
    Card c = { 0 };
    char* tok = strtok(buf, "##");
    if (!tok) return c;

    strcpy(c.card_id, tok);
    tok = strtok(NULL, "##"); strcpy(c.password, tok);
    tok = strtok(NULL, "##"); c.status = atoi(tok);
    tok = strtok(NULL, "##"); c.create_time = stringToTime(tok);
    tok = strtok(NULL, "##"); c.expire_time = stringToTime(tok);
    tok = strtok(NULL, "##"); c.total_used = atof(tok);
    tok = strtok(NULL, "##"); strcpy(c.last_use_time, tok);
    tok = strtok(NULL, "##"); c.use_count = atoi(tok);
    tok = strtok(NULL, "##"); c.balance = atof(tok);
    tok = strtok(NULL, "##"); c.is_deleted = atoi(tok);
    return c;
}

int loadAllCardsFromFile(Card* outCards) {
    FILE* fp = fopen(CARD_FILE, "r");
    if (!fp) return 0;
    char buf[512];
    int i = 0;
    while (fgets(buf, 512, fp)) {
        outCards[i++] = parseCardLine(buf);
    }
    fclose(fp);
    return i;
}
