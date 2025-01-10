#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/DamagePipeline/FireInstance.h"

class CriticalHitProcess
{
public:
	static void EvaluateCriticalHitMods(FireInstance *fireInstance);
	static void RollForCriticalHits(FireInstance *fireInstance);
	static void ApplyCriticalHitDamage(FireInstance *fireInstance);

private:
	static void EvaluateCriticalChanceMods(FireInstance *fireInstance);
	static void EvaluateCriticalDamageMods(FireInstance *fireInstance);
	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
};