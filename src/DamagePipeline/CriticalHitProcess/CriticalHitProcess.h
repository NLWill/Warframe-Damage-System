#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class CriticalHitProcess
{
public:
static void EvaluateCriticalHitProcess(shared_ptr<DamageInstance> damageInstance);

private:
	static void EvaluateCriticalChanceMods(shared_ptr<DamageInstance> damageInstance);
	static void EvaluateCriticalDamageMods(shared_ptr<DamageInstance> damageInstance);
	static void EvaluateCriticalTierMods(shared_ptr<DamageInstance> damageInstance);
	static void RollForCriticalHits(shared_ptr<DamageInstance> damageInstance);
	static void ApplyCriticalHitDamage(shared_ptr<DamageInstance> damageInstance);

	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
};