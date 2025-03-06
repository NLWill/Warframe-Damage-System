#pragma once
#include <memory>
#include "src/Mods/IModManager.h"
#include "src/Mods/ModSlotType.h"

class ModManager : public IModManager{
	public:
	ModManager(const std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails, const std::vector<std::string> compatabilityTags);
	virtual void AddMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex);
	virtual void AddMod(std::shared_ptr<Mod> mod);
	virtual void RemoveMod(unsigned int modSlotIndex);
	virtual void RemoveMod(std::string name);
	virtual std::shared_ptr<Mod> GetMod(unsigned int modSlotIndex);
	virtual int GetModSlotCount();
	virtual void PringCurrentModConfig();

	virtual std::vector<std::shared_ptr<IModEffect>> GetAllModEffects(ModUpgradeType upgradeType);

	private:
	std::vector<std::shared_ptr<Mod>> equippedMods;	// List of the mod slots, nullptr for an absent mod
	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails;
	std::vector<std::string> weaponCompatabilityTags;

	bool CanEquipMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex, bool outputWarnings = false);
	bool CheckValidModSlotIndex(unsigned int modSlotIndex);
	bool CheckModSlotRestrictions(std::shared_ptr<Mod> mod, unsigned int modSlotIndex);
};