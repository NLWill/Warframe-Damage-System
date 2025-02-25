#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/DamagePipeline/DamageInstance.h"

class CriticalHitProcess
{
public:
	static void ApplyCriticalHitMods(DamageInstance *damageInstance, bool calculateAverageValue = false);

private:
	static void EvaluateCriticalChanceMods(DamageInstance *damageInstance, bool calculateAverageValue = false);
	static void EvaluateCriticalDamageMods(DamageInstance *damageInstance, bool calculateAverageValue = false);
	static void EvaluateCriticalTierMods(DamageInstance *damageInstance, bool calculateAverageValue = false);
	static void RollForCriticalHits(DamageInstance *damageInstance);
	static void ApplyCriticalHitDamage(DamageInstance *damageInstance);
	static void ApplyAverageCriticalHitDamage(DamageInstance *damageInstance);

	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
};