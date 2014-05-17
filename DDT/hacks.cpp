#include <Windows.h>
#include "hacks.h"
#include "PatternFind.h"
#include <stdio.h>

HINSTANCE gM;

PFSEARCH pf;
LPVOID lpvDDBase = NULL;
DWORD dwDDSize = 0;

LPVOID healthAddr;

void MsgBoxAddy(DWORD addy)
{
	char szBuffer[1024];
	sprintf(szBuffer, "Addy: %02x", addy);
	::MessageBox(NULL, szBuffer, "Title", MB_OK);
}

void SetGM(HINSTANCE hI)
{
	gM = hI;
}

void GetAddress(int i)
{
	switch (i)
	{
	case 1:

		GetModuleSize(gM, &lpvDDBase, &dwDDSize);

		FindPattern("8B 45 ? 89 46 ? ? ? 7D ? C7 46 ? ? ? ? ? 8D", &pf, lpvDDBase, dwDDSize);
		healthAddr = pf.lpvResult;

		MsgBoxAddy((DWORD)healthAddr);

		break;

	case 2:
		break;

	case 3:
		break;
	}
}