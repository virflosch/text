#ifndef GLOBAL_H
#define GLOBAL_H

#include <time.h>

#define CARD_ID_LEN 18
#define PWD_LEN 8
#define TIME_LEN 20

typedef enum {
    CARD_OFFLINE = 0,
    CARD_ONLINE = 1
} CardStatus;

typedef struct {
    // 实验要求 10 个字段
    char card_id[CARD_ID_LEN + 1];
    char password[PWD_LEN + 1];
    CardStatus status;
    time_t create_time;
    time_t expire_time;
    float total_used;
    char last_use_time[TIME_LEN];
    int use_count;
    float balance;
    int is_deleted;
} Card;

#endif
