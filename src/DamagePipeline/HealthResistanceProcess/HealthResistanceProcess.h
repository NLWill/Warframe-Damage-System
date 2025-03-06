#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class HealthResistanceProcess
{
public:
	static void EvaluateAndApplyHealthResistanceDamageReduction(std::shared_ptr<DamageInstance> damageInstance);

private:
};