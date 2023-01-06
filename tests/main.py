import sys
from ctypes import CDLL, c_int
from tkinter import Button, Tk

from progressbar import ProgressBar

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
        return self._dll.init()

    def set_progress(self, progress: int, total: int) -> int:
        return self._dll.set_value(c_int(progress), c_int(total))

    def end(self) -> int:
        return self._dll.end()


progressbar = ProgressBar()

curr = 0


def clicked():
    global curr
    progressbar.init()
    curr += 10
    if curr > 100:
        curr = 0
    progressbar.set_progress(curr, 100)


def main():
    window = Tk()
    window.title('progressbar test')
    window.geometry('350x200')
    btn = Button(window, text='Click here', command=clicked)
    btn.grid(column=0, row=0)
    window.mainloop()
    progressbar.end()


if __name__ == '__main__':
    main()
