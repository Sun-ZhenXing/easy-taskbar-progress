#define DLL_EXPORT extern "C" __declspec(dllexport)

DLL_EXPORT void init();
DLL_EXPORT void set_mode(int mode);
DLL_EXPORT void set_value(int value, int total);
DLL_EXPORT void end();
