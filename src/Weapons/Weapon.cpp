#pragma once
#include "include/Weapons/Weapon.h"
#include "src/Services/ServiceLocator.h"

class Weapon{
	public:	
	WeaponData data;
	std::vector<Mod*> equippedMods;
	
	Weapon(WeaponData _data){
		data = _data;
		equippedMods = {};
	}
	Weapon(WeaponData _data, std::vector<Mod*> &mods){
		data = _data;
		equippedMods = mods;
	}

	void AddMod(Mod *mod, int index)
	{
		if (index >= data.modSlotCount || index < 0){
			ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to index outside mod slot count.");
			return;
		}

		// Check that there are no other mods to clash with the compatability tag or name
		for (int i = 0; i < equippedMods.size(); i++)
		{
			if (i==index) continue;

			if (equippedMods[i]->name == mod->name){
				ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to identical mod already equipped.");
				return;
			}

			if (equippedMods[i]->compatabilityTag == mod->compatabilityTag && mod->compatabilityTag != ""){
				ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to duplicate compatability tag.");
				return;
			}
		}
		
		

		equippedMods[index] = mod;
	}

	void RemoveMod(int index)
	{
		if (index >= data.modSlotCount || index < 0){
			return;
		}

		equippedMods[index] = nullptr;
	}

	void RemoveMod(std::string name)
	{
		for (int i = 0; i < equippedMods.size(); i++)
		{
			if (equippedMods[i]->name == name){
				equippedMods[i] = nullptr;
				return;
			}
		}
		
	}

	void PringCurrentModConfig(){
		ServiceLocator::GetLogger().Log(data.name);
		for (int i = 0; i < equippedMods.size(); i++)
		{
			string msg = i + ": " + equippedMods[i]->name;
			msg += ", Rank " + equippedMods[i]->rank;
			msg += "/" + equippedMods[i]->maxRank;
			ServiceLocator::GetLogger().Log(msg);
		}
		
	}
};