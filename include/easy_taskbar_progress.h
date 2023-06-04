#ifndef EASY_TASKBAR_PROGRESS
#define EASY_TASKBAR_PROGRESS

#include <windows.h>

void init();
void init_with_hwnd(HWND hwnd);
void set_mode(int mode);
void set_value(int value, int total);
void end();

#endif  // EASY_TASKBAR_PROGRESS
