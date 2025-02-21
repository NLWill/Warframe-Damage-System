#pragma once
#include "src/Mods/ModManagerInterface.h"
#include "src/WeaponsReworked/Weapon.h"
#include "src/Mods/ModSlotType.h"

class ModManager : public ModManagerInterface{
	public:
	ModManager(Weapon *parent);
	virtual void AddMod(Mod *mod, int modSlotIndex);
	virtual void AddMod(Mod *mod);
	virtual void RemoveMod(int modSlotIndex);
	virtual void RemoveMod(std::string name);
	virtual Mod *GetMod(int modSlotIndex);
	virtual int GetModSlotCount();
	virtual void PringCurrentModConfig();

	virtual std::vector<ModEffectBase *> GetAllModEffects(ModUpgradeType upgradeType);

	private:
	Weapon *parent;
	std::vector<Mod *> equippedMods;	// List of the mod slots, nullptr for an absent mod
	std::vector<ModPolarity> modSlotPolarity;	// Polarity of the associated mod slot
	std::vector<ModSlotType> modSlotRestrictions;	// Mod slot restrictions, such as exilus, aura, arcane etc...

	void GenerateModSlots(int normalModSlotCount, int auraSlotCount, int exilusSlotCount, int arcaneSlotCount);
	bool CanEquipMod(Mod *mod, int modSlotIndex);
	bool CheckValidModSlotIndex(int modSlotIndex);
	bool CheckModSlotRestrictions(Mod *mod, int modSlotIndex);
};