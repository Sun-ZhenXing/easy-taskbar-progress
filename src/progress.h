#include <Windows.h>
#include <crtdbg.h>
#include <shobjidl_core.h>

class TaskBarProgress {
   public:
    TaskBarProgress(HWND hWnd)
        : m_hWnd(hWnd), m_pTaskBarList3(NULL) {}
    virtual ~TaskBarProgress() {
        _ASSERT(m_pTaskBarList3 == NULL);
    }

    void startProgressMode(int mode = TBPF_NORMAL);
    void endProgressMode();
    void setProgress(ULONGLONG progressValue, ULONGLONG progressTotal);

   private:
    HWND m_hWnd;
    ITaskbarList3* m_pTaskBarList3;
};
