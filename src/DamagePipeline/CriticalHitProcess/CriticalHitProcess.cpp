#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamagePipeline.h"

void CriticalHitProcess::EvaluateCriticalHitMods(FireInstance *fireInstance)
{
	EvaluateCriticalChanceMods(fireInstance);
	EvaluateCriticalDamageMods(fireInstance);
}

void CriticalHitProcess::EvaluateCriticalChanceMods(FireInstance *fireInstance)
{
	float baseCriticalChance = fireInstance->weapon->data.attacks.at(fireInstance->attackName).criticalChance;
	fireInstance->moddedCriticalChance = DamagePipeline::EvaluateAndApplyModEffects(fireInstance, ModUpgradeType::WEAPON_CRIT_CHANCE, baseCriticalChance);
}

void CriticalHitProcess::EvaluateCriticalDamageMods(FireInstance *fireInstance)
{
	// Fetch all mods that affect the crit chance
	std::vector<ModEffectBase *> criticalDamageEffects = fireInstance->GetAllModEffects(ModUpgradeType::WEAPON_CRIT_DAMAGE);

	fireInstance->moddedCriticalDamage = fireInstance->weapon->data.attacks.at(fireInstance->attackName).criticalDamage;
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(criticalDamageEffects);

	// Apply the baseBonus
	fireInstance->moddedCriticalDamage += addToBaseBonus;
	// Quantise the CD
	fireInstance->moddedCriticalDamage = std::round(fireInstance->moddedCriticalDamage / (criticalDamageQuantisationResolution)) * criticalDamageQuantisationResolution;
	// Apply the stacking_Multiply
	fireInstance->moddedCriticalDamage *= 1 + stackingMultiplyBonus;
	// Apply the multiplicativeBonus
	fireInstance->moddedCriticalDamage *= multiplyBonus;
	// Apply the flatAdditiveBonus
	fireInstance->moddedCriticalDamage += flatAdditiveBonus;

	// Handle any set operations and return if there are any
	for (int i = 0; i < criticalDamageEffects.size(); i++)
	{
		if (criticalDamageEffects[i]->GetModOperationType() == ModOperationType::SET)
		{
			fireInstance->moddedCriticalDamage = criticalDamageEffects[i]->GetModValue();
			return;
		}
	}
}

void CriticalHitProcess::RollForCriticalHits(FireInstance *fireInstance)
{
	for (DamageInstance *bullet : fireInstance->damageInstances)
	{
		// Calculate the critical tier by performing a weigted rounding
		int criticalTier = ServiceLocator::GetRNG().WeightedFloorCeiling(fireInstance->moddedCriticalChance);
		bullet->critTier = criticalTier;

		// Double the CD if headshot
	}
}

void CriticalHitProcess::ApplyCriticalHitDamage(FireInstance *fireInstance)
{
	for (auto damageInstance : fireInstance->damageInstances)
	{
		// Calculate the final critical multiplier from the CD and crit tier
		float criticalMultiplier = 1 + damageInstance->critTier * (fireInstance->moddedCriticalDamage - 1);

		// Multiply the DamageInstance by the criticalDamage
		*damageInstance *= criticalMultiplier;
	}
}