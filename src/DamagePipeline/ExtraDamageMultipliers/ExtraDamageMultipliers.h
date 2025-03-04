#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class ExtraDamageMultipliers
{
public:
	static void EvaluateAndApplyExtraMultipliers(shared_ptr<DamageInstance> damageInstance);

private:
};