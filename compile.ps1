Remove-Item .\build\ -Force -Recurse
Remove-Item .\x64\ -Force -Recurse
Remove-Item .\x86\ -Force -Recurse

mkdir x64 -Force
mkdir x86 -Force

cmake -B ./build -G "Visual Studio 17 2022" -T host=x64 -A x64 .
cmake --build ./build --config Release --target ALL_BUILD -j 4 --
move ./build/build/Release/easy-taskbar-progress.dll x64
move ./build/Release/easy-taskbar-progress.exp x64
move ./build/Release/easy-taskbar-progress.lib x64

Remove-Item .\build\ -Force -Recurse

cmake -B ./build -G "Visual Studio 17 2022" -T host=x86 -A win32 .
cmake --build ./build --config Release --target ALL_BUILD -j 4 --
move ./build/build/Release/easy-taskbar-progress.dll x86
move ./build/Release/easy-taskbar-progress.exp x86
move ./build/Release/easy-taskbar-progress.lib x86

7z a -r easy-taskbar-progress_x64.zip ./x64/*
7z a -r easy-taskbar-progress_x86.zip ./x86/*
