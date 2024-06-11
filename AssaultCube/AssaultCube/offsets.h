#pragma once
#include <Windows.h>
#include <iostream>
//	float x; //0x4
//	float y;//0x8
//	float z;//0xC
//	float pitch;//0x34
//	float yaw;//0x38
//	int health;//0xf8
//	int armor;//0xfc
//	int pistolAmmo;//0x13c
//	int rifleAmmo;//0x150
//	int grenades;//0x158
//	int currentAmmo;// base + 374 , 14 , 0 [MLP]


#define localPlayer 0x10f4f4
#define healthOffset 0xF8
#define armorOffset 0xFC
#define xOffset 0x4
#define yOffset 0x8
#define zOffset 0xC
#define pitchOffset 0x34
#define yawOffset 0x38
#define pistolAmmoOffset 0x13C
#define rifleAmmoOffset 0x150
#define grenades 0x158
#define currentAmmoMLP 0x374, 0x14, 0x0
#define recoil 0x374, 0xc, 0x120
#define frrf 0x178
#define frpl 0x164
#define enterP 0x0
#define client L"ac_client.exe"