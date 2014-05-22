#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <psapi.h>
#include <DbgHelp.h>
#pragma  comment(lib, "psapi")
#pragma  comment(lib, "dbghelp")

void MsgBoxAddress(DWORD addy);

DWORD getGameProcessBaseAddress(DWORD dwProcId);
BOOL GetModuleSize(HMODULE hModule, LPVOID* lplpBase, LPDWORD lpdwSize);

bool __stdcall MaskCompare(const unsigned char* lpData, const unsigned char* lpPattern, const char* pszMask);
DWORD __stdcall FindPattern(unsigned char* lpData, unsigned int nDataSize, const unsigned char* lpPattern, const char* pszMask);

DWORD GetAddress(char *pattern, char *mask);