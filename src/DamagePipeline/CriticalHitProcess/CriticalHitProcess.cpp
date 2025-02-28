#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamagePipeline.h"
#define DEBUG_CRIT_PROCESS false

void CriticalHitProcess::EvaluateCriticalChanceMods(DamageInstance *damageInstance)
{
	if (!damageInstance->moddedCriticalChance.needsToBeCalculated){
		// This has already been run, so no need to do it again
		return;
	}

	float baseCriticalChance = damageInstance->damageData.critChance;
	damageInstance->moddedCriticalChance.Set(DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_CHANCE, baseCriticalChance));

#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetLogger().Log("Final Critical Chance = " + std::to_string(damageInstance->moddedCriticalChance.Get()));
#endif
}

void CriticalHitProcess::EvaluateCriticalDamageMods(DamageInstance *damageInstance)
{
	if (!damageInstance->moddedCriticalDamage.needsToBeCalculated){
		// This has already been run, so no need to do it again
		return;
	}

	// Fetch all mods that affect the crit chance
	std::vector<ModEffectBase *> criticalDamageEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_CRIT_DAMAGE);

	float moddedCriticalDamage = damageInstance->damageData.critDamage;
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, criticalDamageEffects);
	// ServiceLocator::GetLogger().Log("Processing critical damage");
	// ServiceLocator::GetLogger().Log("addToBaseBonus = " + std::to_string(addToBaseBonus));
	// ServiceLocator::GetLogger().Log("stackingMultiplyBonus = " + std::to_string(stackingMultiplyBonus));
	// ServiceLocator::GetLogger().Log("multiplyBonus = " + std::to_string(multiplyBonus));
	// ServiceLocator::GetLogger().Log("flatAdditiveBonus = " + std::to_string(flatAdditiveBonus));

	// Apply the baseBonus
	moddedCriticalDamage += addToBaseBonus;
	// Quantise the CD
	moddedCriticalDamage = std::round(moddedCriticalDamage / (criticalDamageQuantisationResolution)) * criticalDamageQuantisationResolution;
	// Apply the stacking_Multiply
	moddedCriticalDamage *= 1 + stackingMultiplyBonus;
	// Apply the multiplicativeBonus
	moddedCriticalDamage *= multiplyBonus;
	// Apply the flatAdditiveBonus
	moddedCriticalDamage += flatAdditiveBonus;

	// Handle any set operations and return if there are any
	for (int i = 0; i < criticalDamageEffects.size(); i++)
	{
		if (criticalDamageEffects[i]->GetModOperationType() == ModOperationType::SET)
		{
			moddedCriticalDamage = criticalDamageEffects[i]->GetModValue(damageInstance);
		}
	}

	// Double the CD if headshot
	if (damageInstance->target->IsBodyPartWeakPoint(damageInstance->targetBodyPart))
	{
		moddedCriticalDamage *= 2;
	}

	damageInstance->moddedCriticalDamage.Set(moddedCriticalDamage);

#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetLogger().Log("Final Critical Damage = " + std::to_string(damageInstance->moddedCriticalDamage.Get()));
#endif
}

void CriticalHitProcess::RollForCriticalHits(DamageInstance *damageInstance)
{
	if (!damageInstance->critTier.needsToBeCalculated){
		// This has already been run, so no need to do it again
		return;
	}

	if (damageInstance->calculateAverageDamage)
	{
		damageInstance->critTier.Set(damageInstance->GetCriticalChance());
	}
	else
	{
		// Calculate the critical tier by performing a weigted rounding
		int criticalTier = ServiceLocator::GetRNG().WeightedFloorCeiling(damageInstance->GetCriticalChance());
		damageInstance->critTier.Set(criticalTier);
	}

#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetLogger().Log("Rolled critical tier " + std::to_string(damageInstance->critTier.Get()));
#endif
}

void CriticalHitProcess::EvaluateCriticalTierMods(DamageInstance *damageInstance)
{
	if (!damageInstance->critTier.needsToBeCalculated){
		// This has already been run, so no need to do it again
		return;
	}

	float baseCriticalTier = damageInstance->GetCriticalTier();
	damageInstance->critTier.Set(DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_TIER, baseCriticalTier));
}

void CriticalHitProcess::ApplyCriticalHitDamage(DamageInstance *damageInstance)
{
	// ServiceLocator::GetLogger().Log("Critical tier = " + std::to_string(damageInstance->critTier));
	// ServiceLocator::GetLogger().Log("Critical damage = " + std::to_string(damageInstance->moddedCriticalDamage));

	// Calculate the final critical multiplier from the CD and crit tier
	float criticalMultiplier = 1 + damageInstance->GetCriticalTier() * (damageInstance->GetCriticalDamage() - 1);
	// ServiceLocator::GetLogger().Log("Critical multiplier = " + std::to_string(criticalMultiplier));

	// Multiply the DamageInstance by the criticalDamage
	*damageInstance *= criticalMultiplier;
}
