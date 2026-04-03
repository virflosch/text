#include "menu.h"
#include "tool.h"
#include "card_service.h"
#include <stdio.h>

void showMainMenu() {
    clearScreen();
    printf("========== 卡管理系统(文件版) ==========\n");
    printf("1. 添加卡\n");
    printf("2. 精确查询卡\n");
    printf("3. 模糊查询卡\n");
    printf("0. 退出\n");
    printf("请选择：");
}

void addCardUI() {
    clearScreen();
    Card c = { 0 };
    printf("输入卡号："); scanf("%s", c.card_id);
    printf("输入密码："); scanf("%s", c.password);
    printf("输入开卡金额："); scanf("%f", &c.balance);

    c.create_time = time(NULL);
    c.expire_time = c.create_time + 31536000;
    c.status = CARD_OFFLINE;
    c.is_deleted = 0;
    getCurrentTimeStr(c.last_use_time);

    int res = addCard(c);
    if (res == 0) printf("添加成功！\n");
    else if (res == -1) printf("卡号已存在！\n");
    else printf("保存文件失败！\n");
}

void queryCardUI() {
    clearScreen();
    char id[20];
    printf("请输入卡号："); scanf("%s", id);
    lpCardNode node = queryCard(id);
    if (!node) {
        printf("无此卡信息！\n");
        return;
    }
    printf("\n===== 卡信息 =====\n");
    printf("卡号：%s\n", node->data.card_id);
    printf("状态：%s\n", node->data.status ? "已上机" : "未上机");
    printf("余额：%.2f\n", node->data.balance);
    printf("累计消费：%.2f\n", node->data.total_used);
    printf("使用次数：%d\n", node->data.use_count);
    printf("最后使用：%s\n", node->data.last_use_time);
}

void fuzzyQueryUI() {
    clearScreen();
    char key[20];
    printf("输入查询关键字："); scanf("%s", key);
    int cnt;
    Card* arr = fuzzyQueryCards(key, &cnt);
    if (!arr) {
        printf("无匹配记录！\n");
        return;
    }
    printf("\n匹配到 %d 条：\n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%d. %s 余额:%.2f\n", i + 1, arr[i].card_id, arr[i].balance);
    }
    free(arr);
}
