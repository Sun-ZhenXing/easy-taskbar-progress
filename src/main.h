#ifndef MAIN_H
#define MAIN_H

#define DLL_EXPORT extern "C" __declspec(dllexport)

#include <windows.h>

DLL_EXPORT void init();
DLL_EXPORT void init_with_hwnd(HWND hwnd);
DLL_EXPORT void set_mode(int mode);
DLL_EXPORT void set_value(int value, int total);
DLL_EXPORT void end();

#endif  // MAIN_H