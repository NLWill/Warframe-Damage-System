#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class ExtraDamageMultipliers
{
public:
	static void EvaluateAndApplyExtraMultipliers(std::shared_ptr<DamageInstance> damageInstance);

private:
};