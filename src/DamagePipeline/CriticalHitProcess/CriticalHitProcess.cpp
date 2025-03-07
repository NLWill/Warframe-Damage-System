#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

#include "src/Services/ServiceLocator.h"
#include "src/Services/RNG/IRNGService.h"
#include <cmath>

#define DEBUG_CRIT_PROCESS false
#if DEBUG_CRIT_PROCESS
#include "src/Services/Logging/ILogService.h"
#endif


void CriticalHitProcess::EvaluateCriticalHitProcess(std::shared_ptr<DamageInstance> damageInstance)
{
	EvaluateCriticalChanceMods(damageInstance);
	EvaluateCriticalDamageMods(damageInstance);
	RollForCriticalHits(damageInstance);
	EvaluateCriticalTierMods(damageInstance);
	ApplyCriticalHitDamage(damageInstance);
}

void CriticalHitProcess::EvaluateCriticalChanceMods(std::shared_ptr<DamageInstance> damageInstance)
{
	if (!damageInstance->moddedCriticalChance.needsToBeCalculated)
	{
		// This has already been run, so no need to do it again
		return;
	}

	float baseCriticalChance = damageInstance->damageData.critChance;
	damageInstance->moddedCriticalChance.Set(ModProcessingFunctions::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_CHANCE, baseCriticalChance));
	damageInstance->moddedCriticalChance.needsToBeCalculated = false;

#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Final Critical Chance = " + std::to_string(damageInstance->moddedCriticalChance.Get()));
#endif
}

void CriticalHitProcess::EvaluateCriticalDamageMods(std::shared_ptr<DamageInstance> damageInstance)
{
	if (!damageInstance->moddedCriticalDamage.needsToBeCalculated)
	{
		// This has already been run, so no need to do it again
		return;
	}

	// Fetch all mods that affect the crit chance
	auto criticalDamageEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_CRIT_DAMAGE);

	float moddedCriticalDamage = damageInstance->damageData.critDamage;
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = ModProcessingFunctions::CalculateModEffects(damageInstance, criticalDamageEffects);
	// ServiceLocator::GetService<ILogService>()->Log("Processing critical damage");
	// ServiceLocator::GetService<ILogService>()->Log("addToBaseBonus = " + std::to_string(addToBaseBonus));
	// ServiceLocator::GetService<ILogService>()->Log("stackingMultiplyBonus = " + std::to_string(stackingMultiplyBonus));
	// ServiceLocator::GetService<ILogService>()->Log("multiplyBonus = " + std::to_string(multiplyBonus));
	// ServiceLocator::GetService<ILogService>()->Log("flatAdditiveBonus = " + std::to_string(flatAdditiveBonus));

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
	for (size_t i = 0; i < criticalDamageEffects.size(); i++)
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
	damageInstance->moddedCriticalDamage.needsToBeCalculated = false;

#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Final Critical Damage = " + std::to_string(damageInstance->moddedCriticalDamage.Get()));
#endif
}

void CriticalHitProcess::RollForCriticalHits(std::shared_ptr<DamageInstance> damageInstance)
{
	if (!damageInstance->critTier.needsToBeCalculated)
	{
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
		int criticalTier = ServiceLocator::GetService<IRNGService>()->WeightedFloorCeiling(damageInstance->GetCriticalChance());
		damageInstance->critTier.Set(criticalTier);
	}

#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Rolled critical tier " + std::to_string(damageInstance->critTier.Get()));
#endif
}

void CriticalHitProcess::EvaluateCriticalTierMods(std::shared_ptr<DamageInstance> damageInstance)
{
	if (!damageInstance->critTier.needsToBeCalculated)
	{
		// This has already been run, so no need to do it again
		return;
	}

	float baseCriticalTier = damageInstance->critTier.Get();
	damageInstance->critTier.Set(ModProcessingFunctions::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_TIER, baseCriticalTier));
	damageInstance->critTier.needsToBeCalculated = false;
}

void CriticalHitProcess::ApplyCriticalHitDamage(std::shared_ptr<DamageInstance> damageInstance)
{
	// ServiceLocator::GetService<ILogService>()->Log("Critical tier = " + std::to_string(damageInstance->critTier));
	// ServiceLocator::GetService<ILogService>()->Log("Critical damage = " + std::to_string(damageInstance->moddedCriticalDamage));

	// Calculate the final critical multiplier from the CD and crit tier
	float criticalMultiplier = 1 + damageInstance->GetCriticalTier() * (damageInstance->GetCriticalDamage() - 1);
	// ServiceLocator::GetService<ILogService>()->Log("Critical multiplier = " + std::to_string(criticalMultiplier));

	// Multiply the DamageInstance by the criticalDamage
	*damageInstance *= criticalMultiplier;
}
