#include "src/Mods/ModManager.h"

#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"

ModManager::ModManager(const std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails, const std::vector<std::string> compatabilityTags, const std::vector<std::string> weaponParents)
{
	this->modSlotDetails = modSlotDetails;
	this->weaponCompatabilityTags = compatabilityTags;
	this->weaponParents = weaponParents;
	equippedMods = {};
	for (size_t i = 0; i < modSlotDetails.size(); i++)
	{
		equippedMods.push_back(nullptr);
	}
}

void ModManager::AddMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex)
{
	// ServiceLocator::GetService<ILogService>()->LogWarning("Starting AddMod()");
	if (CanEquipMod(mod, modSlotIndex, true))
	{
		equippedMods[modSlotIndex] = mod;
	}
}

void ModManager::AddMod(std::shared_ptr<Mod> mod)
{
	for (size_t i = 0; i < equippedMods.size(); i++)
	{
		if (equippedMods[i] == nullptr && CanEquipMod(mod, i))
		{
			equippedMods[i] = mod;
			return;
		}
	}
	ServiceLocator::GetService<ILogService>()->LogWarning("Failed to equip mod " + mod->name);
}

bool ModManager::CanEquipMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex, bool outputWarnings)
{
	// Check that the index provided is a valid slot index
	if (!CheckValidModSlotIndex(modSlotIndex))
	{
		if (outputWarnings)
			ServiceLocator::GetService<ILogService>()->LogWarning("Unable to equip mod due to modSlotIndex outside mod slot count.");
		return false;
	}
	// ServiceLocator::GetService<ILogService>()->LogWarning("Passed valid index test");

	// Check that mod slot restrictions allow the mod to be placed at this id
	if (!CheckModSlotRestrictions(mod, modSlotIndex))
	{
		if (outputWarnings)
			ServiceLocator::GetService<ILogService>()->LogWarning("Unable to equip mod due to mod slot restriction: " + modSlotDetails[modSlotIndex].first.ToString());
		return false;
	}

	// Check that this mod may be equipped on the associated weapon type
	bool matchesParentTag = false;
	for (size_t i = 0; i < weaponParents.size(); i++)
	{
		if (mod->itemCompatability == weaponParents[i])
		{
			matchesParentTag = true;
			break;
		}
	}
	if (!matchesParentTag)
	{
		if (outputWarnings)
			ServiceLocator::GetService<ILogService>()->LogWarning("Unable to equip mod due to weapon incompatability with mod itemCompatability: " + mod->itemCompatability);
		return false;
	}

	// Check that the mod matches the compatability tag of the weapon
	for (size_t i = 0; i < mod->incompatabilityTags.size(); i++)
	{
		for (size_t j = 0; j < weaponCompatabilityTags.size(); j++)
		{
			if (mod->incompatabilityTags[i] == weaponCompatabilityTags[j])
			{
				if (outputWarnings)
					ServiceLocator::GetService<ILogService>()->LogWarning("Unable to equip mod due to clash of incompatability tag on weapon: " + mod->incompatabilityTags[i]);
				return false;
			}
		}
	}

	// Check that there are no other mods to clash with the mod parent or name
	for (size_t i = 0; i < equippedMods.size(); i++)
	{
		// No point checking the slot where it is to be equipped, as it will replace that one anyway
		if (i == modSlotIndex || equippedMods[i] == nullptr)
		{
			continue;
		}

		if (equippedMods[i]->name == mod->name)
		{
			if (outputWarnings)
				ServiceLocator::GetService<ILogService>()->LogWarning("Unable to equip mod due to mod with same name already equipped: " + mod->name);
			return false;
		}

		if (equippedMods[i]->parent == mod->parent && equippedMods[i]->parent != "")
		{
			if (outputWarnings)
				ServiceLocator::GetService<ILogService>()->LogWarning("Unable to equip mod due to another mod with the same parent tag: " + equippedMods[i]->name);
			return false;
		}
	}

	// It passed all tests and thus may be equipped
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

bool ModManager::CheckModSlotRestrictions(std::shared_ptr<Mod> mod, unsigned int modSlotIndex)
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
		ServiceLocator::GetService<ILogService>()->LogWarning("Unable to remove mod due to index out of range");
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
	ServiceLocator::GetService<ILogService>()->LogWarning("Unable to find mod to remove: " + name);
}

std::shared_ptr<Mod> ModManager::GetMod(unsigned int modSlotIndex)
{
	if (!CheckValidModSlotIndex(modSlotIndex))
	{
		ServiceLocator::GetService<ILogService>()->LogWarning("Failed to obtain mod due to modSlotIndex outside mod slot count.");
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
		if (equippedMods[i] == nullptr)
		{
			ServiceLocator::GetService<ILogService>()->Log(std::to_string(i) + ": No mod equipped");
			continue;
		}

		std::string msg = std::to_string(i) + ": " + equippedMods[i]->name;
		msg += ", Rank " + std::to_string(equippedMods[i]->rank);
		msg += "/" + std::to_string(equippedMods[i]->maxRank);
		ServiceLocator::GetService<ILogService>()->Log(msg);
	}
}

std::vector<std::shared_ptr<IModEffect>> ModManager::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<std::shared_ptr<IModEffect>> relevantEffects = {};

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
