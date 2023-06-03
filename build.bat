rm -rf build
rm -rf x86
rm -rf x64
mkdir x64
mkdir x86
cmake -B ./build -G "Visual Studio 17 2022" -T host=x64 -A x64 .
cmake --build ./build --config Release --target ALL_BUILD -j4
cp build/build/Release/easy-taskbar-progress.dll x64/TaskbarLib.dll
rm -rf build
cmake -B ./build -G "Visual Studio 17 2022" -T host=x86 -A win32 .
cmake --build ./build --config Release --target ALL_BUILD -j4
cp build/build/Release/easy-taskbar-progress.dll x86/TaskbarLib.dll
rm -rf build
pause
