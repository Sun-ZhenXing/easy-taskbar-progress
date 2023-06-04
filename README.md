# Easy Taskbar Progress

Windows 下的超简单的工具栏进度条 DLL。可嵌入任意 GUI 程序。

![demo](images/2023-01-08-22-45-51.png)

如果你需要在你的 C/C++ 项目中使用，可以复制 `progress.cpp` 和 `progress.h` 直接使用，更加灵活。如果你没有编译环境，可以直接下载 Release 中的 DLL 文件，然后调用 DLL 接口即可，如果你正在使用 Python，可以直接复制 `tests/easy_progressbar.py` 文件直接使用。

注意 Windows 11 并不完全遵循下方的模式设置，例如设置进度时如果当前模式是加载中（`TBPF_INDETERMINATE`）也能继续显示，但是本项目仍然兼容。

> 考虑到 Qt 6 已经不支持各个平台下的任务栏进度条了，所以创建了一个 Windows 版本的进度条应用，参考了 Windows API ，并且大量参考了 [Shane 的博客](http://shanekirk.com/2014/12/making-progress-on-the-windows-taskbar/)。
>
> 本项目也是作为学习 GitHub Actions 和 CMake 的学习材料。作者也是通过学习创建了此项目。

- [Easy Taskbar Progress](#easy-taskbar-progress)
  - [编译](#编译)
  - [导出 ABI](#导出-abi)
  - [测试效果](#测试效果)
  - [开源协议](#开源协议)

## 编译

你可以在 Release 中直接下载 DLL。

```bash
cmake -B ./build -G "Visual Studio 16 2019" -T host=x64 -A x64 .
cmake --build ./build --config Release --target ALL_BUILD -j 4 --
```

其中 `-G "Visual Studio 16 2019"` 要指定为你的 VS 版本。

如果 VS 配置正确将生成 `.\build\build\Release\easy-taskbar-progress.dll`。

## 导出 ABI

这些接口都默认没有返回值。

| 接口                              | 功能                             |
| --------------------------------- | -------------------------------- |
| `init()`                          | 开始进度条功能                   |
| `init_with_hwnd(HWND hwnd)`       | 开始进度条功能，指定窗口句柄     |
| `set_mode(int mode)`              | 设置模式                         |
| `set_value(int value, int total)` | 设置值，最终表示为 `value/total` |
| `end()`                           | 结束进度条功能                   |

**注意**：`init()` 的时间节点决定了它内部保存的窗口句柄（`HWND`），只有当程序运行在包含窗口事件循环的时候，`init()` 才能正确初始化为当前激活窗口。

可以多次 `init()` 或者 `end()`，但是所有操作之前必须进行 `init()`，而 `end()` 后如果想继续操作必须再次 `init()`。建议只进行一次 `init()`，只有当当前窗体释放时才调用 `end()`，可以使用 `set_mode(0)` 来结束，而使用 `set_mode(2)` 开始。

支持的模式：

| 模式                 | 值    | 含义                     |
| -------------------- | ----- | ------------------------ |
| `TBPF_NOPROGRESS`    | `0x0` | 没有加载条               |
| `TBPF_INDETERMINATE` | `0x1` | 正在加载中               |
| `TBPF_NORMAL`        | `0x2` | 正常，显示加载进度       |
| `TBPF_ERROR`         | `0x4` | 错误，显示为红色的加载条 |
| `TBPF_PAUSED`        | `0x8` | 中断，显示为黄色的加载条 |

## 测试效果

Python >= 3.7

```bash
python tests/main.py
```

每次点击，进度条都会加 10%，然后循环。

## 开源协议

MIT.
