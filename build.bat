@echo off

rmdir /Q /S build
rmdir /Q /S x86
rmdir /Q /S x64

mkdir x64
mkdir x86

cmake -B ./build -G "Visual Studio 17 2022" -T host=x64 -A x64 .
cmake --build ./build --config Release --target ALL_BUILD -j 4 --

copy build\build\Release\easy-taskbar-progress.dll x64\ /Y
copy build\Release\easy-taskbar-progress.exp x64\ /Y
copy build\Release\easy-taskbar-progress.lib x64\ /Y

rmdir /Q /S build

cmake -B ./build -G "Visual Studio 17 2022" -T host=x86 -A win32 .
cmake --build ./build --config Release --target ALL_BUILD -j 4 --

copy build\build\Release\easy-taskbar-progress.dll x86\ /Y
copy build\Release\easy-taskbar-progress.exp x86\ /Y
copy build\Release\easy-taskbar-progress.lib x86\ /Y

rmdir /Q /S build
