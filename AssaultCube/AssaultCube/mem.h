#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>


DWORD GetProcId(const wchar_t* procname);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);



namespace mem {

	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
}