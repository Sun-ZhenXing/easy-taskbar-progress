#include "main.h"
#include "progress.h"

HWND g_hwnd;
TaskBarProgress g_progress(NULL);

// init progress bar
void init() {
    CoInitialize(NULL);
    g_hwnd = ::GetActiveWindow();
    g_progress = TaskBarProgress(g_hwnd);
    g_progress.startProgressMode();
}

// init progress bar with hwnd
void init(HWND hwnd) {
    CoInitialize(NULL);
    g_progress = TaskBarProgress(hwnd);
    g_progress.startProgressMode();
}

// set progress bar mode, must be init first
void set_mode(int mode) {
    g_progress.startProgressMode(mode);
}

// set progress bar value, must be init first, and be TBPF_NORMAL mode
void set_value(int value, int total) {
    g_progress.setProgress(value, total);
}

// release progress bar
void end() {
    g_progress.endProgressMode();
    CoUninitialize();
}
