#include <Windows.h>

DWORD GetAddress(char *pattern, char *mask);

void PatchHealth(DWORD address);
void PatchMana(DWORD address);
void PatchGold(DWORD address);