Remove-Item .\build\ -Force -Recurse
Remove-Item .\x64\ -Force -Recurse
Remove-Item .\x86\ -Force -Recurse

New-Item x64 -ItemType "directory" -Force
New-Item x86 -ItemType "directory" -Force

cmake -B ./build -G "Visual Studio 17 2022" -T host=x64 -A x64 .
cmake --build ./build --config Release --target ALL_BUILD -j 4 --

Copy-Item ./build/build/Release/easy-taskbar-progress.dll x64/
Copy-Item ./build/Release/easy-taskbar-progress.exp x64/
Copy-Item ./build/Release/easy-taskbar-progress.lib x64/

Remove-Item .\build\ -Force -Recurse

cmake -B ./build -G "Visual Studio 17 2022" -T host=x86 -A win32 .
cmake --build ./build --config Release --target ALL_BUILD -j 4 --

Copy-Item ./build/build/Release/easy-taskbar-progress.dll x86/
Copy-Item ./build/Release/easy-taskbar-progress.exp x86/
Copy-Item ./build/Release/easy-taskbar-progress.lib x86/
