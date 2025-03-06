#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class FactionDamageProcess{
	public:
	static void EvaluateAndApplyFactionDamage(std::shared_ptr<DamageInstance> damageInstance);
};