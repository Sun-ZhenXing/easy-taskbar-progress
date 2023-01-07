import sys
from ctypes import CDLL, c_int
from tkinter import Button, Tk

DLL_PATH = './build/build/Release/easy-taskbar-progress.dll'


class ProgressBar:
    def __init__(self) -> None:
        if sys.platform == 'win32':
            self._dll = CDLL(DLL_PATH)
        else:
            raise NotImplementedError('Only Windows is supported')
        self._is_init = False

    def init(self) -> int:
        if self._is_init:
            return 0
        self._is_init = True
        return self._dll.init()

    def set_mode(self, mode: int) -> int:
        if not self._is_init:
            raise RuntimeError('ProgressBar is not initialized')
        return self._dll.set_mode(c_int(mode))

    def set_progress(self, progress: int, total: int) -> int:
        if not self._is_init:
            raise RuntimeError('ProgressBar is not initialized')
        return self._dll.set_value(c_int(progress), c_int(total))

    def end(self) -> int:
        return self._dll.end()


progressbar = ProgressBar()

curr_progress = 0
curr_mode = 0


def running():
    global curr_progress
    progressbar.init()
    curr_progress += 10
    if curr_progress > 100:
        curr_progress = 0
    print('progress:', curr_progress)
    progressbar.set_progress(curr_progress, 100)


def change_mode():
    global curr_mode
    if curr_mode < 1:
        curr_mode = 1
    elif curr_mode >= 8:
        curr_mode = 0
    else:
        curr_mode <<= 1
    print('mode:', curr_mode)
    progressbar.set_mode(curr_mode)


def main():
    window = Tk()
    window.title('progressbar test')
    window.geometry('350x200')
    btn1 = Button(window, text='+10%', command=running)
    btn2 = Button(window, text='mode', command=change_mode)
    btn1.grid(column=0, row=0)
    btn2.grid(column=1, row=0)
    window.mainloop()
    progressbar.end()


if __name__ == '__main__':
    main()
