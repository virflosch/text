#ifndef GLOBAL_H
#define GLOBAL_H

// 全局配置常量（可直接修改）
#define MAX_CARD_NUM 50       // 最大卡数量
#define CARD_ID_LEN 18        // 卡号最大长度
#define PWD_LEN 8             // 密码最大长度

// 卡状态枚举（0=未上机，1=已上机）
typedef enum {
    CARD_OFFLINE = 0,
    CARD_ONLINE = 1
} CardStatus;

// 卡信息结构体（新增字段只需在这里加）
typedef struct {
    char card_id[CARD_ID_LEN + 1];   // 卡号
    char password[PWD_LEN + 1];      // 密码
    CardStatus status;              // 状态
    float balance;                  // 余额
    float total_used;               // 累计使用金额
    int use_count;                  // 使用次数
    char last_use_time[20];         // 上次使用时间（字符串）
} Card;

// 全局变量声明（供其他文件使用）
extern Card aCard[MAX_CARD_NUM];
extern int nCount;

#endif // GLOBAL_H