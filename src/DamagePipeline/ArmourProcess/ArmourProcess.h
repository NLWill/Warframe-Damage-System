#pragma once
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/DamagePipeline/DamageInstance.h"

class ArmourProcess
{
public:
	static void EvaluateAndApplyArmourDamageReduction(DamageInstance *damageInstance);

private:
};