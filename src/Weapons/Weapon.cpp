#include "include/Weapons/Weapon.h"
#include "src/Services/ServiceLocator.h"
#include <algorithm>

Weapon::Weapon(WeaponData &_data) : data(_data)
{
	equippedMods = {};
}

Weapon::Weapon(WeaponData &_data, std::vector<Mod *> &mods) : data(_data)
{
	data = _data;
	equippedMods = mods;
}

Weapon *Weapon::GetNullWeapon()
{
	auto nullAttackData = AttackData({}, 0, 1, 0, 1, "Hitscan");
	std::map<std::string, AttackData> nullAttackDataMap = {};
	nullAttackDataMap[nullAttackData.attackName] = nullAttackData;
	WeaponData data = WeaponData("Null Weapon", nullAttackDataMap);

	return new Weapon(data);
}

void Weapon::AddMod(Mod *mod, int index)
{
	if (index >= data.modSlotCount || index < 0)
	{
		ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to index outside mod slot count.");
		return;
	}

	//Check that the mod matches the compatability tag of the weapon
	if (false){
		throw "Not Implemented Exception";
	}

	// Check that there are no other mods to clash with the compatability tag or name
	for (int i = 0; i < equippedMods.size(); i++)
	{
		if (i == index)
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

	equippedMods[index] = mod;
}

void Weapon::RemoveMod(int index)
{
	if (index >= data.modSlotCount || index < 0)
	{
		return;
	}

	equippedMods[index] = nullptr;
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