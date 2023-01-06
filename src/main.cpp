#include <Windows.h>
#include <shobjidl_core.h>
#include <iostream>

#include "main.h"

class TaskBarProgress {
   public:
    TaskBarProgress(HWND hWnd)
        : m_hWnd(hWnd), m_pTaskBarList3(NULL) {}
    virtual ~TaskBarProgress() {
        _ASSERT(m_pTaskBarList3 == NULL);
    }
    void startProgressMode();
    void endProgressMode();
    void setProgress(ULONGLONG progressValue, ULONGLONG progressTotal);

   private:
    HWND m_hWnd;
    ITaskbarList3* m_pTaskBarList3;
};

void TaskBarProgress::startProgressMode() {
    if (!m_hWnd)
        return;
    if (!m_pTaskBarList3) {
        HRESULT hr = ::CoCreateInstance(
            CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void**)&m_pTaskBarList3);
        if (hr != S_OK)
            return;
    }
    m_pTaskBarList3->SetProgressState(m_hWnd, TBPF_NORMAL);
    m_pTaskBarList3->SetProgressValue(m_hWnd, 0, 100);
}

void TaskBarProgress::setProgress(ULONGLONG progressValue, ULONGLONG progressTotal) {
    if (!m_pTaskBarList3 || !m_hWnd)
        return;
    m_pTaskBarList3->SetProgressValue(m_hWnd, progressValue, progressTotal);
}

void TaskBarProgress::endProgressMode() {
    if (!m_pTaskBarList3 || !m_hWnd)
        return;
    m_pTaskBarList3->SetProgressState(m_hWnd, TBPF_NOPROGRESS);
    m_pTaskBarList3->Release();
    m_pTaskBarList3 = NULL;
}

HWND g_hwnd;
TaskBarProgress g_progress(NULL);

void init() {
    CoInitialize(NULL);
    g_hwnd = ::GetActiveWindow();
    g_progress = TaskBarProgress(g_hwnd);
    g_progress.startProgressMode();
}

void set_value(int value, int total) {
    g_progress.setProgress(value, total);
}

void end() {
    g_progress.endProgressMode();
    CoUninitialize();
}
