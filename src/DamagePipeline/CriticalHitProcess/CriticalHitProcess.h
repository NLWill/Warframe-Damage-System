#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class CriticalHitProcess
{
public:
	static void ApplyCriticalHitDamage(DamageInstance *damageInstance);

	static void EvaluateCriticalChanceMods(DamageInstance *damageInstance);
	static void EvaluateCriticalDamageMods(DamageInstance *damageInstance);
	static void EvaluateCriticalTierMods(DamageInstance *damageInstance);
	static void RollForCriticalHits(DamageInstance *damageInstance);

private:
	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
};