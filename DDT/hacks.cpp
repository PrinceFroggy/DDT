#include "functions.h"
#include "hacks.h"

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