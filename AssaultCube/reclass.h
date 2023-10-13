#pragma once
#include <Windows.h>
#include "geom.h"




class EntityBase
{
public:
	char pad_0000[4]; //0x0000
	Vector3 HeadPos; //0x0004
	char pad_0010[24]; //0x0010
	Vector3 PlayerPos; //0x0028
	Vector2 MousePos; //0x0034
	char pad_003C[176]; //0x003C
	uint32_t Vida; //0x00EC
	uint32_t Escudo; //0x00F0
	char pad_00F4[272]; //0x00F4
	char PlayerName[16]; //0x0204
	char pad_0214[10]; //0x0214
}; //Size: 0x021E
