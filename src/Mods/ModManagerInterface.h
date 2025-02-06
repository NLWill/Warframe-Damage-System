#pragma once
#include "src/Mods/ModBase.h"
#include <vector>

class ModManagerInterface
{
public:
	virtual void AddMod(Mod *mod, int modSlotIndex) = 0;
	virtual void RemoveMod(int index) = 0;
	virtual void RemoveMod(std::string name) = 0;
	virtual Mod *GetMod(int modSlotIndex) = 0;
	virtual int GetModSlotCount() = 0;
	virtual void PringCurrentModConfig() = 0;

	virtual std::vector<ModEffectBase *> GetAllModEffects(ModUpgradeType upgradeType) = 0;

protected:
};