#include "SDK.h"
#include "mem.h"


int main() {
	//Get Process ID
	DWORD procID = GetProcId(client);
	//handle to process with all access
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);
	//get module base address
	uintptr_t moduleBase = GetModuleBaseAddress(procID, client);
	//get local player
	uintptr_t localPlrPtr = moduleBase + localPlayer;
	uintptr_t localPlr = FindDMAAddy(hProcess, localPlrPtr, { enterP });
	uintptr_t health = localPlr + healthOffset;
	uintptr_t armor = localPlr + armorOffset;
	uintptr_t firerateRifle = localPlr + frrf;
	uintptr_t fireratePistol = localPlr + frpl;
	bool on1 = false, on2 = false, on3 = false, unHealth = false, noRecoil = false;
	bool frRifle = false, frPistol = false;
	while (true) {
		int healthMod = 1337;
		int armorMod = 1337;
		int ammoMod = 1337;
		unsigned int fireRateR = -20;
		unsigned int fireRateP = -20;

		uintptr_t currentAmmo = FindDMAAddy(hProcess, localPlrPtr, { currentAmmoMLP });
		int healthtest = ReadInt(hProcess, health, healthMod);
		int armortest = ReadInt(hProcess, armor, armorMod);
		int currentAmmoPlr = ReadInt(hProcess, currentAmmo, ammoMod);
		int test1 = ReadInt(hProcess, firerateRifle, fireRateR);
		int test2 = ReadInt(hProcess, fireratePistol, fireRateP);

		if (GetAsyncKeyState(VK_NUMPAD1) & 1) { // modify health
			on1 = !on1;
			if (on1) {
				WriteInt(hProcess, health, healthMod);
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 1) { // modify armor
			on2 = !on2;
			if (on2) {
				WriteInt(hProcess, armor, armorMod);
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD3) & 1) { // modify ammo
			on3 = !on3;
			if (on3) {
				WriteInt(hProcess, currentAmmo, ammoMod);
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
			unHealth = !unHealth;
		}
		if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
			noRecoil = !noRecoil;
		}
		if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
			frRifle = !frRifle;
		}
		if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
			frPistol = !frPistol;
		}
		if (unHealth) {
			mem::PatchEx((BYTE*)health, (BYTE*)&healthMod, sizeof(healthMod), hProcess);
			printf("[ON] UNLIMITED HEALTH \n");
		}
		else {
			printf("[OFF] UNLIMITED HEALTH \n");
		}
		if (noRecoil) {
			mem::NopEx((BYTE*)(moduleBase + 0x63786), 10, hProcess);
			printf("[ON] NO RECOIL \n");
		}
		else {
			mem::PatchEx((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10, hProcess);
			printf("[OFF] NO RECOIL\n");
		}
		if (frRifle) {
			WriteInt(hProcess, firerateRifle, fireRateR);
			printf("[ON] FIRERATE HACK RIFLE \n");
		}
		else {
			printf("[OFF] FIRERATE HACK RIFLE \n");
		}
		if (frPistol) {
			WriteInt(hProcess, fireratePistol, fireRateP);
			printf("[ON] FIRERATE HACK PISTOL \n");
		}
		else {
			printf("[OFF] FIRERATE HACK PISTOL \n");
		}
		printf("Health : %d\n", healthtest);
		printf("Armor : %d\n", armortest);
		printf("Current Ammo in Hand : %d\n", currentAmmoPlr);
		Sleep(3);
		system("CLS");
	}

	return 0;
}