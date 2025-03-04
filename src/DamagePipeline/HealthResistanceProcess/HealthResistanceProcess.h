#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class HealthResistanceProcess
{
public:
	static void EvaluateAndApplyHealthResistanceDamageReduction(shared_ptr<DamageInstance> damageInstance);

private:
};