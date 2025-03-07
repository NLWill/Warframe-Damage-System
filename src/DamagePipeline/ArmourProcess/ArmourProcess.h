#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class ArmourProcess
{
public:
	static void EvaluateAndApplyArmourDamageReduction(std::shared_ptr<DamageInstance> damageInstance);

private:
};