#pragma once
#include "src/Weapons/WeaponData.h"
#include "src/Mods/ModBase.h"
#include<string>

class Weapon{
	public:
	WeaponData data;
	std::vector<Mod*> equippedMods;

	Weapon(WeaponData _data);
	Weapon(WeaponData _data, std::vector<Mod*> &mods);

	void AddMod(Mod* mod, int index);
	void RemoveMod(int index);
	void RemoveMod(std::string name);
	void PringCurrentModConfig();
};