#pragma once
#include <memory>
#include "src/Mods/ModManagerInterface.h"
#include "src/Mods/ModSlotType.h"

class ModManager : public ModManagerInterface{
	public:
	ModManager(const std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails, const std::vector<std::string> compatabilityTags);
	virtual void AddMod(shared_ptr<Mod> mod, unsigned int modSlotIndex);
	virtual void AddMod(shared_ptr<Mod> mod);
	virtual void RemoveMod(unsigned int modSlotIndex);
	virtual void RemoveMod(std::string name);
	virtual shared_ptr<Mod> GetMod(unsigned int modSlotIndex);
	virtual int GetModSlotCount();
	virtual void PringCurrentModConfig();

	virtual std::vector<shared_ptr<ModEffectBase>> GetAllModEffects(ModUpgradeType upgradeType);

	private:
	std::vector<shared_ptr<Mod>> equippedMods;	// List of the mod slots, nullptr for an absent mod
	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails;
	std::vector<std::string> weaponCompatabilityTags;

	bool CanEquipMod(shared_ptr<Mod> mod, unsigned int modSlotIndex, bool outputWarnings = false);
	bool CheckValidModSlotIndex(unsigned int modSlotIndex);
	bool CheckModSlotRestrictions(shared_ptr<Mod> mod, unsigned int modSlotIndex);
};