#include "functions.h"
#include "hacks.h"

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

DWORD HealthEntry;
DWORD HealthReturn;

__declspec(naked) void HealthHook()
{
	__asm
	{
		mov eax, [ebp + 0x0C]
		cmp eax, [esi + 0x54]
		jng Exit
		mov [esi + 0x54], eax
		
		Exit:
		jmp HealthReturn
	}
}

void PatchHealth(DWORD address)
{
	auto caveDest = ((int)HealthHook - (int)address) - 5;
	HealthReturn = address + 6;

	*(BYTE*)(address + 0x00) = 0xE9;
	*(UINT*)(address + 0x01) = caveDest;
	*(BYTE*)(address + 0x05) = 0x90;
}

DWORD ManaEntry;
DWORD ManaReturn;

__declspec(naked) void ManaHook()
{
	__asm
	{
		mov eax, [ebp + 0x08]
		cmp ecx, [eax + 0x60]
		jng Exit
		mov [eax + 0x60], ecx

		Exit:
		jmp ManaReturn
	}
}

void PatchMana(DWORD address)
{
	auto caveDest = ((int)ManaHook - (int)address) - 5;
	ManaReturn = address + 6;

	*(BYTE*)(address + 0x00) = 0xE9;
	*(UINT*)(address + 0x01) = caveDest;
	*(BYTE*)(address + 0x05) = 0x90;
}

DWORD GoldEntry;
DWORD GoldReturn;

__declspec(naked) void GoldHook()
{
	__asm
	{
		cmp [eax], eax
		cmp ecx, [eax + 0x4C]
		jng Exit
		mov [eax + 0x4C], ecx

		Exit:
		jmp GoldReturn
	}
}

void PatchGold(DWORD address)
{
	auto caveDest = ((int)GoldHook - (int)address) - 5;
	GoldReturn = address + 5;

	*(BYTE*)(address + 0x00) = 0xE9;
	*(UINT*)(address + 0x01) = caveDest;
}