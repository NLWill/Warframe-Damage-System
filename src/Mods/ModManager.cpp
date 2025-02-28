#include "src/Mods/ModManager.h"

ModManager::ModManager(Weapon *parent)
{
	this->parent = parent;
	GenerateModSlots(parent->weaponData.normalModSlotCount, parent->weaponData.auraSlotCount, parent->weaponData.exilusSlotCount, parent->weaponData.arcaneSlotCount);
}

void ModManager::GenerateModSlots(int normalModSlotCount, int auraSlotCount, int exilusSlotCount, int arcaneSlotCount)
{
	equippedMods = {};
	modSlotRestrictions = {};
	modSlotPolarity = {};
	for (int i = 0; i < normalModSlotCount; i++)
	{
		equippedMods.push_back(nullptr);
		modSlotRestrictions.push_back(ModSlotType::MST_NORMAL);
	}
	for (int i = 0; i < auraSlotCount; i++)
	{
		equippedMods.push_back(nullptr);
		modSlotRestrictions.push_back(ModSlotType::MST_AURA);
	}
	for (int i = 0; i < exilusSlotCount; i++)
	{
		equippedMods.push_back(nullptr);
		modSlotRestrictions.push_back(ModSlotType::MST_EXILUS);
	}
	for (int i = 0; i < arcaneSlotCount; i++)
	{
		equippedMods.push_back(nullptr);
		modSlotRestrictions.push_back(ModSlotType::MST_ARCANE);
	}

	// Get polarity data from the weapon's data struct
	for (int i = 0; i < parent->weaponData.modPolarities.size(); i++)
	{
		modSlotPolarity.push_back(parent->weaponData.modPolarities[i]);
	}

	if (modSlotPolarity.size() != equippedMods.size())
	{
		ServiceLocator::GetLogger().LogError("Error when generating Mod slots, polarity size does not match number of mod slots.");
	}
}

void ModManager::AddMod(Mod *mod, int modSlotIndex)
{
	// ServiceLocator::GetLogger().LogWarning("Starting AddMod()");
	if (CanEquipMod(mod, modSlotIndex))
	{
		equippedMods[modSlotIndex] = mod;
	}
}

void ModManager::AddMod(Mod *mod)
{
	for (int i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i] == nullptr && CanEquipMod(mod, i))
		{
			equippedMods[i] = mod;
			return;
		}
	}
	ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to no valid empty mod slots");
}

bool ModManager::CanEquipMod(Mod *mod, int modSlotIndex)
{
	// Check that the index provided is a valid slot index
	if (!CheckValidModSlotIndex(modSlotIndex))
	{
		ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to modSlotIndex outside mod slot count.");
		return false;
	}
	// ServiceLocator::GetLogger().LogWarning("Passed valid index test");

	// Check that mod slot restrictions allow the mod to be placed at this id
	if (!CheckModSlotRestrictions(mod, modSlotIndex))
	{
		ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to mod slot restriction: " + modSlotRestrictions[modSlotIndex].ToString());
		return false;
	}

	// Check that the mod matches the compatability tag of the weapon
	for (int i = 0; i < mod->incompatabilityTags.size(); i++)
	{
		for (int j = 0; j < parent->weaponData.compatabilityTags.size(); j++)
		{
			if (mod->incompatabilityTags[i] == parent->weaponData.compatabilityTags[j])
			{
				ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to clash of incompatability tag on weapon: " + mod->incompatabilityTags[i]);
				return false;
			}
		}
	}

	// Check that there are no other mods to clash with the mod parent or name
	for (int i = 0; i < equippedMods.size(); i++)
	{
		// ServiceLocator::GetLogger().LogWarning("Iterating over mod " + std::to_string(i));
		if (i == modSlotIndex || equippedMods[i] == nullptr)
			continue;

		if (equippedMods[i]->name == mod->name)
		{
			ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to mod with same name already equipped: " + mod->name);
			return false;
		}

		if (equippedMods[i]->parent == mod->parent && equippedMods[i]->parent != "")
		{
			ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to another mod with the same parent tag: " + equippedMods[i]->name);
			return false;
		}
	}

	// It evidently passed all tests and thus may be equipped
	return true;
}

bool ModManager::CheckValidModSlotIndex(int modSlotIndex)
{
	if (modSlotIndex >= equippedMods.size() || modSlotIndex < 0)
	{
		return false;
	}
	return true;
}

bool ModManager::CheckModSlotRestrictions(Mod *mod, int modSlotIndex)
{
	ModSlotType slotRestriction = modSlotRestrictions[modSlotIndex];

	if (slotRestriction == ModSlotType::MST_NORMAL)
	{
		if (mod->slotType == ModSlotType::MST_NORMAL || mod->slotType == ModSlotType::MST_EXILUS)
		{
			return true;
		}
	}
	else if (slotRestriction == ModSlotType::MST_EXILUS)
	{
		if (mod->slotType == ModSlotType::MST_EXILUS)
		{
			return true;
		}
	}
	else if (slotRestriction == ModSlotType::MST_AURA)
	{
		if (mod->slotType == ModSlotType::MST_AURA)
		{
			return true;
		}
	}
	else if (slotRestriction == ModSlotType::MST_ARCANE)
	{
		if (mod->slotType == ModSlotType::MST_ARCANE)
		{
			return true;
		}
	}

	return false;
}

void ModManager::RemoveMod(int modSlotIndex)
{
	if (modSlotIndex >= equippedMods.size() || modSlotIndex < 0)
	{
		ServiceLocator::GetLogger().LogWarning("Unable to remove mod due to index out of range");
		return;
	}

	equippedMods[modSlotIndex] = nullptr;
}

void ModManager::RemoveMod(std::string name)
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

Mod *ModManager::GetMod(int modSlotIndex)
{
	if (!CheckValidModSlotIndex(modSlotIndex))
	{
		ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to modSlotIndex outside mod slot count.");
		return nullptr;
	}

	return equippedMods[modSlotIndex];
}

int ModManager::GetModSlotCount()
{
	return equippedMods.size();
}

void ModManager::PringCurrentModConfig()
{
	ServiceLocator::GetLogger().Log(parent->weaponData.name);
	for (int i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i] == nullptr){
			ServiceLocator::GetLogger().Log(std::to_string(i) + ": No mod equipped");
			continue;
		}			

		string msg = std::to_string(i) + ": " + equippedMods[i]->name;
		msg += ", Rank " + std::to_string(equippedMods[i]->rank);
		msg += "/" + std::to_string(equippedMods[i]->maxRank);
		ServiceLocator::GetLogger().Log(msg);
	}
}

std::vector<ModEffectBase *> ModManager::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<ModEffectBase *> relevantEffects = {};

	for (int i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i] == nullptr)
		{
			continue;
		}

		for (int j = 0; j < equippedMods[i]->GetModEffects().size(); j++)
		{
			if (equippedMods[i]->GetModEffects()[j]->GetUpgradeType() == upgradeType)
			{
				relevantEffects.push_back(equippedMods[i]->GetModEffects()[j]);
			}
		}
	}

	return relevantEffects;
}
