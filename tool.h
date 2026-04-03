#ifndef TOOL_H
#define TOOL_H

#include "global.h"

void clearScreen();
void pauseProgram();
void getCurrentTimeStr(char* str);
time_t stringToTime(char* pTime);

#endif
