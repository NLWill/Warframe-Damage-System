#pragma once
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/DamagePipeline/DamageInstance.h"

class BaseDamageProcess{
	public:
	static void EvaluateAndApplyBaseDamageMods(shared_ptr<DamageInstance> damageInstance);

	private:
};