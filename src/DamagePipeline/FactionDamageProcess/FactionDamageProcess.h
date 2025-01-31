#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class FactionDamageProcess{
	public:
	static void EvaluateAndApplyFactionDamage(DamageInstance *damageInstance);
};