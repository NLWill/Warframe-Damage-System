#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class CriticalHitProcess
{
public:
static void EvaluateCriticalHitProcess(std::shared_ptr<DamageInstance> damageInstance);

private:
	static void EvaluateCriticalChanceMods(std::shared_ptr<DamageInstance> damageInstance);
	static void EvaluateCriticalDamageMods(std::shared_ptr<DamageInstance> damageInstance);
	static void EvaluateCriticalTierMods(std::shared_ptr<DamageInstance> damageInstance);
	static void RollForCriticalHits(std::shared_ptr<DamageInstance> damageInstance);
	static void ApplyCriticalHitDamage(std::shared_ptr<DamageInstance> damageInstance);

	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
};