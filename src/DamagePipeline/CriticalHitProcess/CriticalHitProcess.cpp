#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamagePipeline.h"
#define DEBUG_CRIT_PROCESS true

void CriticalHitProcess::ApplyCriticalHitMods(DamageInstance *damageInstance, bool calculateAverageValue)
{
	EvaluateCriticalChanceMods(damageInstance, calculateAverageValue);
	EvaluateCriticalDamageMods(damageInstance, calculateAverageValue);

	if (calculateAverageValue){
		EvaluateCriticalTierMods(damageInstance, true);
		ApplyAverageCriticalHitDamage(damageInstance);
	}
	else {
		RollForCriticalHits(damageInstance);
		EvaluateCriticalTierMods(damageInstance);
		ApplyCriticalHitDamage(damageInstance);
	}
	
}

void CriticalHitProcess::EvaluateCriticalChanceMods(DamageInstance *damageInstance, bool calculateAverageValue) 
{
	float baseCriticalChance = damageInstance->damageData.critChance;
	damageInstance->moddedCriticalChance = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_CHANCE, baseCriticalChance);

	#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetLogger().Log("Final Critical Chance = " + std::to_string(damageInstance->moddedCriticalChance));
	#endif
}

void CriticalHitProcess::EvaluateCriticalDamageMods(DamageInstance *damageInstance, bool calculateAverageValue)
{
	// Fetch all mods that affect the crit chance
	std::vector<ModEffectBase *> criticalDamageEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_CRIT_DAMAGE);

	damageInstance->moddedCriticalDamage = damageInstance->damageData.critDamage;
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

	#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetLogger().Log("Final Critical Damage = " + std::to_string(damageInstance->moddedCriticalDamage));
	#endif
}

void CriticalHitProcess::RollForCriticalHits(DamageInstance *damageInstance)
{
	// Calculate the critical tier by performing a weigted rounding
	int criticalTier = ServiceLocator::GetRNG().WeightedFloorCeiling(damageInstance->moddedCriticalChance);
	damageInstance->critTier = criticalTier;
	
	#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetLogger().Log("Rolled critical tier " + std::to_string(damageInstance->critTier));
	#endif
}

void CriticalHitProcess::EvaluateCriticalTierMods(DamageInstance *damageInstance, bool calculateAverageValue)
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

void CriticalHitProcess::ApplyAverageCriticalHitDamage(DamageInstance *damageInstance)
{
	float criticalMultiplier = 1 + damageInstance->moddedCriticalChance * (damageInstance->moddedCriticalDamage -1);

	*damageInstance *= criticalMultiplier;
}
