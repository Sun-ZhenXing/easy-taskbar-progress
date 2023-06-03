import sys
from ctypes import CDLL, c_int
from tkinter import Button, Tk

DLL_PATH = "./build/build/Release/easy-taskbar-progress.dll"


class ProgressBar:
    def __init__(self) -> None:
        if sys.platform == "win32":
            self._dll = CDLL(DLL_PATH)
        else:
            raise NotImplementedError("Only Windows is supported")
        self._is_init = False

    def init(self) -> int:
        ret = self._dll.init()
        self._is_init = True
        return ret

    def set_mode(self, mode: int) -> int:
        if not self._is_init:
            raise RuntimeError("ProgressBar is not initialized")
        return self._dll.set_mode(c_int(mode))

    def set_progress(self, progress: int, total: int) -> int:
        if not self._is_init:
            raise RuntimeError("ProgressBar is not initialized")
        return self._dll.set_value(c_int(progress), c_int(total))

    def end(self) -> int:
        return self._dll.end()


class ProgressBarTest:
    def __init__(self) -> None:
        self.progressbar = ProgressBar()
        self.curr_progress = 0
        self.curr_mode = 0

    def running(self):
        if self.curr_progress == 0:
            self.progressbar.init()
        self.curr_progress += 10
        if self.curr_progress > 100:
            self.curr_progress = 0
        print("progress:", self.curr_progress)
        self.progressbar.set_progress(self.curr_progress, 100)

    def change_mode(self):
        if not self.progressbar._is_init:
            self.progressbar.init()
        if self.curr_mode < 1:
            self.curr_mode = 1
        elif self.curr_mode >= 8:
            self.curr_mode = 0
        else:
            self.curr_mode <<= 1
        print("mode:", self.curr_mode)
        self.progressbar.set_mode(self.curr_mode)


def main():
    window = Tk()
    window.title("progressbar test")
    window.geometry("350x200")
    progressbar_test = ProgressBarTest()
    btn1 = Button(window, text="+10%", command=progressbar_test.running)
    btn2 = Button(window, text="mode", command=progressbar_test.change_mode)
    btn1.grid(column=0, row=0)
    btn2.grid(column=1, row=0)
    window.mainloop()
    progressbar_test.progressbar.end()


if __name__ == "__main__":
    main()
