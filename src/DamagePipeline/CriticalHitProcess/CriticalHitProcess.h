#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/DamagePipeline/FireInstance.h"

class CriticalHitProcess{
	public:
	static void EvaluateCriticalHit(FireInstance* instance);

	private:	
	static constexpr float criticalDamageQuantisationResolution = (float)32 / 4095;
	static void RollForCriticalHit(DamageInstance* instance, float criticalChance, float criticalDamage);
};