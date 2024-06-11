#pragma once
#include "offsets.h"

int ReadInt(HANDLE hProcess, uintptr_t ptr, int buffer) {
	int test = buffer;
	ReadProcessMemory(hProcess, (BYTE*)ptr, &test, sizeof(test), 0);
	return test;
}

float ReadFloat(HANDLE hProcess, uintptr_t ptr, float buffer) {
	float test = buffer;
	ReadProcessMemory(hProcess, (BYTE*)ptr, &test, sizeof(test), 0);
	return test;
}

void WriteInt(HANDLE hProcess, uintptr_t ptr, int buffer) {
	int test = buffer;
	WriteProcessMemory(hProcess, (BYTE*)ptr, &test, sizeof(test), 0);
}

void WriteFloat(HANDLE hProcess, uintptr_t ptr, float buffer) {
	float test = buffer;
	WriteProcessMemory(hProcess, (BYTE*)ptr, &test, sizeof(test), 0);
}


extern bool on1, on2, on3;
extern bool unHealth;
extern bool noRecoil;