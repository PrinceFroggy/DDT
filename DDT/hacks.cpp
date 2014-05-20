#include "functions.h"
#include "hacks.h"

LPVOID GetAddress(char *pattern, char *mask)
{
	HINSTANCE game;
	LPVOID base = 0;
	DWORD size = 0;
	LPVOID Addr;

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
			char info[1024]={0};
			sprintf_s(info,1024,"%08X - %d", mbi.BaseAddress, mbi.RegionSize);
			OutputDebugStringA(info);

			Addr = (LPVOID)FindPattern((unsigned char*)mbi.BaseAddress, mbi.RegionSize, (BYTE*)pattern, mask);
			
			if (Addr != 0)
			{
				MsgBoxAddress((DWORD)Addr);
				break;
			}
		}		
	}

	return Addr;
}