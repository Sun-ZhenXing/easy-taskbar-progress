import sys
from ctypes import CDLL, c_int

DLL_PATH = "./build/build/Release/easy-taskbar-progress.dll"

TBPF_NOPROGRESS = 0x0
TBPF_INDETERMINATE = 0x1
TBPF_NORMAL = 0x2
TBPF_ERROR = 0x4
TBPF_PAUSED = 0x8


class EasyProgressBar:
    def __init__(self, dll_path: str = DLL_PATH) -> None:
        """Windows progress bar."""
        if sys.platform == "win32":
            self._dll = CDLL(dll_path)
        else:
            raise NotImplementedError("Only Windows is supported")
        self._is_init = False

    def init(self) -> int:
        """Initialize the progress bar."""
        ret = self._dll.init()
        self._is_init = True
        return ret

    def set_mode(self, mode: int) -> int:
        """Set the progress bar mode."""
        if not self._is_init:
            raise RuntimeError("ProgressBar is not initialized")
        return self._dll.set_mode(c_int(mode))

    def set_progress(self, progress: int, total: int) -> int:
        """Set the progress bar progress and total."""
        if not self._is_init:
            raise RuntimeError("ProgressBar is not initialized")
        return self._dll.set_value(c_int(progress), c_int(total))

    def end(self) -> int:
        """End the progress bar."""
        return self._dll.end()
