#include "src/WeaponsReworked/Weapon.h"
#include "src/Mods/ModManager.h"

WeaponReworked::WeaponReworked(WeaponDataReworked &weaponData) : weaponData{weaponData}
{
	//modManager = new ModManager(this);
}

std::vector<ModEffectBase *> WeaponReworked::GetAllWeaponModEffects(ModUpgradeType upgradeType)
{
	std::vector<ModEffectBase *> relevantEffects;// = modManager->GetAllModEffects(upgradeType);

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