#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamagePipeline.h"

void CriticalHitProcess::EvaluateCriticalChanceMods(DamageInstance *damageInstance)
{
	float baseCriticalChance = damageInstance->weapon->weaponData.attacks.at(damageInstance->attackName).criticalChance;
	damageInstance->moddedCriticalChance = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_CHANCE, baseCriticalChance);
}

void CriticalHitProcess::EvaluateCriticalDamageMods(DamageInstance *damageInstance)
{
	// Fetch all mods that affect the crit chance
	std::vector<ModEffectBase *> criticalDamageEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_CRIT_DAMAGE);

	damageInstance->moddedCriticalDamage = damageInstance->weapon->weaponData.attacks.at(damageInstance->attackName).criticalDamage;
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, criticalDamageEffects);
	// ServiceLocator::GetLogger().Log("Processing critical damage");
	// ServiceLocator::GetLogger().Log("addToBaseBonus = " + std::to_string(addToBaseBonus));
	// ServiceLocator::GetLogger().Log("stackingMultiplyBonus = " + std::to_string(stackingMultiplyBonus));
	// ServiceLocator::GetLogger().Log("multiplyBonus = " + std::to_string(multiplyBonus));
	// ServiceLocator::GetLogger().Log("flatAdditiveBonus = " + std::to_string(flatAdditiveBonus));

	// Apply the baseBonus
	damageInstance->moddedCriticalDamage += addToBaseBonus;
	// Quantise the CD
	damageInstance->moddedCriticalDamage = std::round(damageInstance->moddedCriticalDamage / (criticalDamageQuantisationResolution)) * criticalDamageQuantisationResolution;
	// Apply the stacking_Multiply
	damageInstance->moddedCriticalDamage *= 1 + stackingMultiplyBonus;
	// Apply the multiplicativeBonus
	damageInstance->moddedCriticalDamage *= multiplyBonus;
	// Apply the flatAdditiveBonus
	damageInstance->moddedCriticalDamage += flatAdditiveBonus;

	// Handle any set operations and return if there are any
	for (int i = 0; i < criticalDamageEffects.size(); i++)
	{
		if (criticalDamageEffects[i]->GetModOperationType() == ModOperationType::SET)
		{
			damageInstance->moddedCriticalDamage = criticalDamageEffects[i]->GetModValue(damageInstance);
		}
	}

	// Double the CD if headshot
	if (damageInstance->target->IsBodyPartWeakPoint(damageInstance->targetBodyPart))
	{
		damageInstance->moddedCriticalDamage *= 2;
	}
}

void CriticalHitProcess::RollForCriticalHits(DamageInstance *damageInstance)
{
	// Calculate the critical tier by performing a weigted rounding
	int criticalTier = ServiceLocator::GetRNG().WeightedFloorCeiling(damageInstance->moddedCriticalChance);
	ServiceLocator::GetLogger().Log("Rolled critical tier " + std::to_string(criticalTier));
	damageInstance->critTier = criticalTier;
}

void CriticalHitProcess::EvaluateCriticalTierMods(DamageInstance *damageInstance)
{
	float baseCriticalTier = damageInstance->critTier;
	damageInstance->critTier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_TIER, baseCriticalTier);
}

void CriticalHitProcess::ApplyCriticalHitDamage(DamageInstance *damageInstance)
{
	// ServiceLocator::GetLogger().Log("Critical tier = " + std::to_string(damageInstance->critTier));
	// ServiceLocator::GetLogger().Log("Critical damage = " + std::to_string(damageInstance->moddedCriticalDamage));

	// Calculate the final critical multiplier from the CD and crit tier
	float criticalMultiplier = 1 + damageInstance->critTier * (damageInstance->moddedCriticalDamage - 1);
	// ServiceLocator::GetLogger().Log("Critical multiplier = " + std::to_string(criticalMultiplier));

	// Multiply the DamageInstance by the criticalDamage
	*damageInstance *= criticalMultiplier;
}