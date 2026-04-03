#include "tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearScreen() { system("cls"); }
void pauseProgram() { system("pause"); }

void getCurrentTimeStr(char* str) {
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    strftime(str, TIME_LEN, "%Y-%m-%d %H:%M", lt);
}

time_t stringToTime(char* pTime) {
    struct tm tm = { 0 };
    sscanf(pTime, "%d-%d-%d %d:%d",
        &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
        &tm.tm_hour, &tm.tm_min);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    return mktime(&tm);
}
