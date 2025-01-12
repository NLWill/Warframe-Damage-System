#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/DamagePipeline/FireInstance.h"

class CriticalHitProcess
{
public:
	static void EvaluateCriticalChanceMods(FireInstance *fireInstance);
	static void EvaluateCriticalDamageMods(FireInstance *fireInstance);
	static void EvaluateCriticalTierMods(FireInstance *fireInstance);
	static void RollForCriticalHits(FireInstance *fireInstance);
	static void ApplyCriticalHitDamage(FireInstance *fireInstance);

private:
	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
};