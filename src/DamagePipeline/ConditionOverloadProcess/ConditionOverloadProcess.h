#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class ConditionOverloadProcess{
	public:
	static void EvaluateAndApplyConditionOverloadDamage(std::shared_ptr<DamageInstance> damageInstance);
};