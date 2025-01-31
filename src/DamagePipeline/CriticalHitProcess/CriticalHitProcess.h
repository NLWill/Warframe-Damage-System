#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/DamagePipeline/DamageInstance.h"

class CriticalHitProcess
{
public:
	static void EvaluateCriticalChanceMods(DamageInstance *damageInstance);
	static void EvaluateCriticalDamageMods(DamageInstance *damageInstance);
	static void EvaluateCriticalTierMods(DamageInstance *damageInstance);
	static void RollForCriticalHits(DamageInstance *damageInstance);
	static void ApplyCriticalHitDamage(DamageInstance *damageInstance);

private:
	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
};