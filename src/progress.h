#ifndef PROGRESS_H
#define PROGRESS_H

#include <Windows.h>
#include <crtdbg.h>
#include <shobjidl_core.h>

class TaskBarProgress {
public:
    TaskBarProgress(HWND hWnd);
    virtual ~TaskBarProgress();

    void startProgressMode(int mode = TBPF_NOPROGRESS);
    void endProgressMode();
    void setProgress(ULONGLONG progressValue, ULONGLONG progressTotal);

private:
    HWND m_hWnd;
    ITaskbarList3* m_pTaskBarList3;
};

#endif  // PROGRESS_H
