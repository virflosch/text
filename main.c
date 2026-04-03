#include <stdio.h>
#include "tool.h"
#include "card_service.h"
#include "menu.h"

int main() {
    initCardList();
    int choice;
    while (1) {
        showMainMenu();
        scanf("%d", &choice);
        switch (choice) {
        case 1: addCardUI(); break;
        case 2: queryCardUI(); break;
        case 3: fuzzyQueryUI(); break;
        case 0: goto end;
        default: printf("输入错误！\n");
        }
        pauseProgram();
    }
end:
    releaseCardList();
    return 0;
}
