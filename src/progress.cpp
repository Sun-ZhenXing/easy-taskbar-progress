#include "progress.h"

TaskBarProgress::TaskBarProgress(HWND hWnd)
    : m_hWnd(hWnd), m_pTaskBarList3(NULL) {}

TaskBarProgress::~TaskBarProgress() {
    _ASSERT(m_pTaskBarList3 == NULL);
}

void TaskBarProgress::startProgressMode(int mode) {
    if (mode != TBPF_NOPROGRESS && mode != TBPF_INDETERMINATE && mode != TBPF_NORMAL && mode != TBPF_ERROR && mode != TBPF_PAUSED)
        return;
    if (!m_hWnd)
        return;
    if (!m_pTaskBarList3) {
        HRESULT hr = ::CoCreateInstance(
            CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void**)&m_pTaskBarList3);
        if (hr != S_OK)
            return;
    }
    m_pTaskBarList3->SetProgressState(m_hWnd, (TBPFLAG)mode);
    if (mode == TBPF_NORMAL)
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
