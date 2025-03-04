#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class FactionDamageProcess{
	public:
	static void EvaluateAndApplyFactionDamage(shared_ptr<DamageInstance> damageInstance);
};