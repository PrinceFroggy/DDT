#include <windows.h>
#include "hacks.h"

extern void Main();

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch(fdwReason)
    {
        case DLL_PROCESS_ATTACH:
			SetGM(hinstDLL);
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Main, NULL, 0, NULL);
            break;
    }
    return TRUE;
}