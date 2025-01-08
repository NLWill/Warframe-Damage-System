#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/Services/ServiceLocator.h"



void CriticalHitProcess::EvaluateCriticalHit(FireInstance* fireInstance)
{
	// Evaluate all mods to get the baseBonus, additiveBonus, multiplicativeBonus, and flatAdditiveBonus


	// Apply the baseBonus


	// Quantise the CD
	fireInstance->moddedCriticalMultiplier = std::round(fireInstance->moddedCriticalMultiplier / (criticalDamageQuantisationResolution)) * criticalDamageQuantisationResolution;

	// Apply the additiveBonus, multiplicativeBonus, and flatAdditiveBonus to the CC and CD





	for (DamageInstance* bullet : fireInstance->damageInstances){
		RollForCriticalHit(bullet, fireInstance->moddedCriticalChance, fireInstance->moddedCriticalMultiplier);
	}
}

void CriticalHitProcess::RollForCriticalHit(DamageInstance* instance, float criticalChance, float criticalDamage)
{
	// Calculate the critical tier by performing a weigted rounding
	int criticalTier = ServiceLocator::GetRNG().WeightedFloorCeiling(criticalChance);
	instance->critTier = criticalTier;

	// Double the CD if headshot


	// Calculate the final critical multiplier from the CD and crit tier
	float criticalMultiplier = 1 + criticalTier * (criticalDamage - 1);

	// Multiply the DamageInstance by the criticalMultiplier
	*instance *= criticalMultiplier;
}
