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
	// Get the base value critical damage
	float moddedCriticalDamage = damageInstance->damageData.critDamage;

	// Determine the total values for each ModOperationType that affect the WEAPON_CRIT_DAMAGE
	std::map<ModOperationType, float> modEffectValues = ModProcessingFunctions::CalculateModEffects(damageInstance, ModUpgradeType::WEAPON_CRIT_DAMAGE);

	// Apply the baseBonus
	moddedCriticalDamage += modEffectValues[ModOperationType::ADD_TO_BASE_VALUE];
	// Quantise the CD
	moddedCriticalDamage = std::round(moddedCriticalDamage / (criticalDamageQuantisationResolution)) * criticalDamageQuantisationResolution;
	// Apply the stacking_Multiply
	moddedCriticalDamage *= 1 + modEffectValues[ModOperationType::STACKING_MULTIPLY];
	// Apply the multiplicativeBonus
	moddedCriticalDamage *= modEffectValues[ModOperationType::MULTIPLY];
	// Apply the flatAdditiveBonus
	moddedCriticalDamage += modEffectValues[ModOperationType::ADD];

	// Handle any set operations and return if there are any
	if (modEffectValues.contains(ModOperationType::SET))
	{
		moddedCriticalDamage = modEffectValues[ModOperationType::SET];
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
#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Critical tier = " + std::to_string(damageInstance->critTier));
	ServiceLocator::GetService<ILogService>()->Log("Critical damage = " + std::to_string(damageInstance->moddedCriticalDamage));
#endif

	// Calculate the final critical multiplier from the CD and crit tier
	float criticalMultiplier = 1 + damageInstance->GetCriticalTier() * (damageInstance->GetCriticalDamage() - 1);
#if DEBUG_CRIT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Critical multiplier = " + std::to_string(criticalMultiplier));
#endif

	// Multiply the DamageInstance by the criticalDamage
	*damageInstance *= criticalMultiplier;
}
