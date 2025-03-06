#pragma once
#include "src/Mods/ModBase.h"
#include <vector>

class IModManager
{
public:
// Add mod at specified mod slot index
	virtual void AddMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex) = 0;
	// Add the mod at the first empty mod slot index that fits all requirements
	virtual void AddMod(std::shared_ptr<Mod> mod) = 0;
	// Remove mod at the specified mod slot index
	virtual void RemoveMod(unsigned int index) = 0;
	// Remove the mod with the specified name
	virtual void RemoveMod(std::string name) = 0;
	// Get the mod data for the specified mod slot index
	virtual std::shared_ptr<Mod> GetMod(unsigned int modSlotIndex) = 0;
	// Get the total number of equippable mods
	virtual int GetModSlotCount() = 0;
	// Output the current mods equipped into the console
	virtual void PringCurrentModConfig() = 0;

	// Fetch all mod effects that operate on the specified upgrade operation
	virtual std::vector<std::shared_ptr<IModEffect>> GetAllModEffects(ModUpgradeType upgradeType) = 0;

protected:
};