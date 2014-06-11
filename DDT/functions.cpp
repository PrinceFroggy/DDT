#include "functions.h"

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

DWORD GetAddress(char *pattern, char *mask)
{
	HINSTANCE game;
	LPVOID base = 0;
	DWORD size = 0;
	DWORD Addr;

	auto procID = ::GetCurrentProcessId();
	game = (HINSTANCE)getGameProcessBaseAddress(procID);

	GetModuleSize(game, &base, &size);

	MEMORY_BASIC_INFORMATION mbi = {0};
	unsigned char *pAddress = NULL, *pEndRegion = NULL;

	DWORD dwProtectionMask = PAGE_EXECUTE_READWRITE;

	while(sizeof(mbi) == VirtualQuery(pEndRegion, &mbi, sizeof(mbi)))
	{
		pAddress = pEndRegion;
		pEndRegion += mbi.RegionSize;

		if (mbi.State & MEM_COMMIT && (mbi.AllocationProtect & dwProtectionMask))
		{
			/*
			char info[1024]={0};
			sprintf_s(info,1024,"%08X - %d", mbi.BaseAddress, mbi.RegionSize);
			OutputDebugStringA(info);
			*/

			Addr = FindPattern((unsigned char*)mbi.BaseAddress, mbi.RegionSize, (BYTE*)pattern, mask);
			
			if (Addr != 0)
			{
				//MsgBoxAddress(Addr);

				break;
			}
		}		
	}

	return Addr;
}
