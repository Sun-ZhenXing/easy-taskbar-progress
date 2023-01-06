# Easy Taskbar Progress

Windows 下的超简单的工具栏进度条 DLL。可嵌入任意 GUI 程序。

![](https://i.328888.xyz/2023/01/06/knDxZ.png)

大量参考了 [Shane 的博客](http://shanekirk.com/2014/12/making-progress-on-the-windows-taskbar/)。

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
| `set_value(int value, int total)` | 设置值，最终表示为 `value/total` |
| `end()`                           | 结束进度条功能                   |

**注意**：`init()` 的时间节点决定了它内部保存的窗口句柄（`HWND`），只有当程序运行在包含窗口事件循环的时候，`init()` 才能正确初始化为当前激活窗口。

## 开源协议

MIT.
