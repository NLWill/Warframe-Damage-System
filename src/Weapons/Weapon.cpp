#include "src/Weapons/Weapon.h"
#include "src/Mods/ModManager.h"

Weapon::Weapon(WeaponData &weaponData) : weaponData{weaponData}
{
	modManager = new ModManager(this);
}

Weapon::~Weapon()
{
	delete modManager;
}

std::vector<ModEffectBase *> Weapon::GetAllWeaponModEffects(ModUpgradeType upgradeType)
{
	std::vector<ModEffectBase *> relevantEffects = modManager->GetAllModEffects(upgradeType);

	for (auto mod : weaponData.defaultSlottedUpgrades)
	{
		if (mod == nullptr)
		{
			continue;
		}

		for (auto modEffect : mod->GetModEffects())
		{
			if (modEffect->GetUpgradeType() == upgradeType)
			{
				relevantEffects.push_back(modEffect);
			}
		}
	}

	// Get all modEffects from the incarnon evolutions and append to the complete vector of effects
	auto incarnonEffects = weaponData.incarnonUpgrades.GetAllModEffects(upgradeType);
	relevantEffects.insert(relevantEffects.end(), incarnonEffects.begin(), incarnonEffects.end());

	return relevantEffects;
}