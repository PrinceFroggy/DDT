#include "functions.h"
#include "hacks.h"

void MsgBoxAddress(DWORD addy)
{
	char szBuffer[1024];

	sprintf(szBuffer, "Address: 0x%08X", addy);

	::MessageBox(NULL, szBuffer, "Result", MB_OK);
}

DWORD getGameProcessBaseAddress(DWORD dwProcId)
{
    MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };

    auto handle = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcId);
    
	if (handle == INVALID_HANDLE_VALUE)
	{
        return 0;
	}

    if (!::Module32First(handle, &me32))
    {
        ::CloseHandle(handle);
        return 0;
    }

    ::CloseHandle(handle);

    return (DWORD)me32.modBaseAddr;
}

BOOL GetModuleSize(HMODULE hModule, LPVOID* lplpBase, LPDWORD lpdwSize) 
{
	if (hModule == GetModuleHandle(NULL)) 
	{
		PIMAGE_NT_HEADERS pImageNtHeaders = ImageNtHeader((PVOID)hModule);

		if (pImageNtHeaders == NULL)
		{
			return FALSE;
		}

		*lplpBase = (LPVOID)hModule;

		*lpdwSize = pImageNtHeaders->OptionalHeader.SizeOfImage;
	} 
	else 
	{
		MODULEINFO  ModuleInfo;

		if (!GetModuleInformation(GetCurrentProcess(), hModule, &ModuleInfo, sizeof(MODULEINFO)))
		{
			return FALSE;
		}

		*lplpBase = ModuleInfo.lpBaseOfDll;

		*lpdwSize = ModuleInfo.SizeOfImage;
	}
	return TRUE;
}

bool __stdcall MaskCompare(const unsigned char* lpData, const unsigned char* lpPattern, const char* pszMask) 
{ 
    for (; *pszMask; ++pszMask, ++lpData, ++lpPattern)
	{
        if (*pszMask == 'x' && *lpData != *lpPattern)
		{
			return false;
		}
	}
	return (*pszMask) == NULL; 
} 

DWORD __stdcall FindPattern(unsigned char* lpData, unsigned int nDataSize, const unsigned char* lpPattern, const char* pszMask) 
{ 
    for (unsigned int x = 0; x < nDataSize; x++) 
	{
		if (MaskCompare(lpData + x, lpPattern, pszMask)) 
		{
			return (DWORD)(lpData + x); 
		}
	}
    return 0; 
}