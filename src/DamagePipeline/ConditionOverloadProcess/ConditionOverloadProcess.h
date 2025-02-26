#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class ConditionOverloadProcess{
	public:
	static void EvaluateAndApplyConditionOverloadDamage(DamageInstance *damageInstance, bool averageDamageCalculation = false);
};