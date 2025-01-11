#include "src/DamagePipeline/FireInstance.h"
#include "src/Services/ServiceLocator.h"

FireInstance::FireInstance(Weapon &_weapon, std::string _attackName)
{
	weapon = &_weapon;
	attackName = _attackName;

	damageInstances = {};

	if (weapon != nullptr && weapon->data.attacks.count(attackName) > 0)
	{
		moddedCriticalChance = weapon->data.attacks.at(attackName).criticalChance;
		moddedCriticalDamage = weapon->data.attacks.at(attackName).criticalDamage;
		moddedStatusChance = weapon->data.attacks.at(attackName).statusChance;
		moddedStatusDamageMultiplier = 1;
		moddedMultishot = weapon->data.attacks.at(attackName).multishot;
	}
	else
	{
		ServiceLocator::GetLogger().LogError("Nullptr provided to weapon field in FireInstance constructor or attack name not found.");

		attackName = weapon->data.attacks.begin()->second.attackName;
		moddedCriticalChance = 0;
		moddedCriticalDamage = 1;
		moddedStatusChance = 0;
		moddedStatusDamageMultiplier = 1;
		moddedMultishot = 1;
	}
}

std::vector<ModEffectBase *> FireInstance::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<ModEffectBase *> relevantEffects = {};

	for (auto mod : weapon->equippedMods)
	{
		for (auto modEffect : mod->GetModEffects())
		{
			if (modEffect->GetUpgradeType() == upgradeType)
			{
				relevantEffects.push_back(modEffect);
			}
		}
	}

	for (auto mod : weapon->data.innateUpgrades)
	{
		for (auto modEffect : mod->GetModEffects())
		{
			if (modEffect->GetUpgradeType() == upgradeType)
			{
				relevantEffects.push_back(modEffect);
			}
		}
	}

	/*
	for (auto mod : target->innateUpgrades){
		for (auto modEffect : mod->GetModEffects()){
			if (modEffect->GetUpgradeType() == upgradeType){
				relevantEffects.push_back(modEffect);
			}
		}
	}
	*/

	return std::vector<ModEffectBase *>();
}