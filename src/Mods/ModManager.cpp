#include "src/Mods/ModManager.h"

ModManager::ModManager(const std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails, const std::vector<std::string> compatabilityTags)
{
	this->modSlotDetails = modSlotDetails;
	this->weaponCompatabilityTags = compatabilityTags;
	equippedMods = {};
	for (size_t i = 0; i < modSlotDetails.size(); i++)
	{
		equippedMods.push_back(nullptr);
	}	
}

void ModManager::AddMod(shared_ptr<Mod> mod, unsigned int modSlotIndex)
{
	// ServiceLocator::GetLogger().LogWarning("Starting AddMod()");
	if (CanEquipMod(mod, modSlotIndex, true))
	{
		equippedMods[modSlotIndex] = mod;
	}
}

void ModManager::AddMod(shared_ptr<Mod> mod)
{
	for (size_t i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i] == nullptr && CanEquipMod(mod, i))
		{
			equippedMods[i] = mod;
			return;
		}
	}
	ServiceLocator::GetLogger().LogWarning("Failed to equip mod due to no valid empty mod slots");
}

bool ModManager::CanEquipMod(shared_ptr<Mod> mod, unsigned int modSlotIndex, bool outputWarnings)
{
	// Check that the index provided is a valid slot index
	if (!CheckValidModSlotIndex(modSlotIndex))
	{
		if (outputWarnings) ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to modSlotIndex outside mod slot count.");
		return false;
	}
	// ServiceLocator::GetLogger().LogWarning("Passed valid index test");

	// Check that mod slot restrictions allow the mod to be placed at this id
	if (!CheckModSlotRestrictions(mod, modSlotIndex))
	{
		if (outputWarnings) ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to mod slot restriction: " + modSlotDetails[modSlotIndex].first.ToString());
		return false;
	}

	// Check that the mod matches the compatability tag of the weapon
	for (size_t i = 0; i < mod->incompatabilityTags.size(); i++)
	{
		for (size_t j = 0; j < weaponCompatabilityTags.size(); j++)
		{
			if (mod->incompatabilityTags[i] == weaponCompatabilityTags[j])
			{
				if (outputWarnings) ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to clash of incompatability tag on weapon: " + mod->incompatabilityTags[i]);
				return false;
			}
		}
	}

	// Check that there are no other mods to clash with the mod parent or name
	for (size_t i = 0; i < equippedMods.size(); i++)
	{
		// ServiceLocator::GetLogger().LogWarning("Iterating over mod " + std::to_string(i));
		if (i == modSlotIndex || equippedMods[i] == nullptr)
			continue;

		if (equippedMods[i]->name == mod->name)
		{
			if (outputWarnings) ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to mod with same name already equipped: " + mod->name);
			return false;
		}

		if (equippedMods[i]->parent == mod->parent && equippedMods[i]->parent != "")
		{
			if (outputWarnings) ServiceLocator::GetLogger().LogWarning("Unable to equip mod due to another mod with the same parent tag: " + equippedMods[i]->name);
			return false;
		}
	}

	// It evidently passed all tests and thus may be equipped
	return true;
}

bool ModManager::CheckValidModSlotIndex(unsigned int modSlotIndex)
{
	if (modSlotIndex >= equippedMods.size())
	{
		return false;
	}
	return true;
}

bool ModManager::CheckModSlotRestrictions(shared_ptr<Mod> mod, unsigned int modSlotIndex)
{
	ModSlotType slotRestriction = modSlotDetails[modSlotIndex].first;

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

void ModManager::RemoveMod(unsigned int modSlotIndex)
{
	if (modSlotIndex >= equippedMods.size())
	{
		ServiceLocator::GetLogger().LogWarning("Unable to remove mod due to index out of range");
		return;
	}

	equippedMods[modSlotIndex] = nullptr;
}

void ModManager::RemoveMod(std::string name)
{
	for (size_t i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i]->name == name)
		{
			equippedMods[i] = nullptr;
			return;
		}
	}
	ServiceLocator::GetLogger().LogWarning("Unable to find mod to remove: " + name);
}

shared_ptr<Mod> ModManager::GetMod(unsigned int modSlotIndex)
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
	for (size_t i = 0; i < equippedMods.size(); i++)
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

std::vector<shared_ptr<IModEffect>> ModManager::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<shared_ptr<IModEffect>> relevantEffects = {};

	for (size_t i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i] == nullptr)
		{
			continue;
		}

		for (size_t j = 0; j < equippedMods[i]->GetModEffects().size(); j++)
		{
			if (equippedMods[i]->GetModEffects()[j]->GetUpgradeType() == upgradeType)
			{
				relevantEffects.push_back(equippedMods[i]->GetModEffects()[j]);
			}
		}
	}

	return relevantEffects;
}
