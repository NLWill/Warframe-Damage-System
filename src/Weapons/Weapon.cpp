#include "src/Weapons/Weapon.h"
#include "src/Services/ServiceLocator.h"
#include <algorithm>

Weapon::Weapon(WeaponData &_data) : data(_data)
{
	equippedMods = {};
	for (int i = 0; i < data.modSlotCount; i++)
	{
		equippedMods.push_back(nullptr);
	}
}

Weapon::Weapon(WeaponData &_data, std::vector<Mod *> &mods) : data(_data)
{
	data = _data;
	equippedMods = mods;
	if (equippedMods.size() < data.modSlotCount)
	{
		for (int i = equippedMods.size(); i < data.modSlotCount; i++)
		{
			equippedMods.push_back(nullptr);
		}
	}
}

void Weapon::AddMod(Mod *mod, int modSlotIndex)
{
	//ServiceLocator::GetLogger().LogWarning("Starting AddMod()");
	if (modSlotIndex >= data.modSlotCount || modSlotIndex < 0)
	{
		ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to modSlotIndex outside mod slot count.");
		return;
	}
	//ServiceLocator::GetLogger().LogWarning("Passed valid index test");

	// Check that the mod matches the compatability tag of the weapon
	if (false)
	{
		throw "Not Implemented Exception";
	}

	// Check that there are no other mods to clash with the compatability tag or name
	for (int i = 0; i < equippedMods.size(); i++)
	{
		//ServiceLocator::GetLogger().LogWarning("Iterating over mod " + std::to_string(i));
		if (i == modSlotIndex || equippedMods[i] == nullptr)
			continue;

		if (equippedMods[i]->name == mod->name)
		{
			ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to identical mod already equipped.");
			return;
		}

		for (std::vector<std::string>::iterator it = equippedMods[i]->incompatabilityTags.begin(); it != equippedMods[i]->incompatabilityTags.end(); ++it)
		{
			if (std::find(mod->incompatabilityTags.begin(), mod->incompatabilityTags.end(), *it) != mod->incompatabilityTags.end())
			{
				ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to duplicate incompatability tag.");
				return;
			}
		}
	}

	equippedMods[modSlotIndex] = mod;
	/*
	for (int i = 0; i < equippedMods.size(); i++)
	{
		printf("Address of value: %p\n", (void*)equippedMods[i]);
	}
	*/
}

void Weapon::RemoveMod(int modSlotIndex)
{
	if (modSlotIndex >= data.modSlotCount || modSlotIndex < 0)
	{
		return;
	}

	equippedMods[modSlotIndex] = nullptr;
}

void Weapon::RemoveMod(std::string name)
{
	for (int i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i]->name == name)
		{
			equippedMods[i] = nullptr;
			return;
		}
	}
	ServiceLocator::GetLogger().LogWarning("Unable to find mod to remove: " + name);
}

void Weapon::PringCurrentModConfig()
{
	ServiceLocator::GetLogger().Log(data.name);
	for (int i = 0; i < equippedMods.size(); i++)
	{
		string msg = i + ": " + equippedMods[i]->name;
		msg += ", Rank " + equippedMods[i]->rank;
		msg += "/" + equippedMods[i]->maxRank;
		ServiceLocator::GetLogger().Log(msg);
	}
}