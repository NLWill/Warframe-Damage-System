#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class BaseDamageProcess{
	public:
	static void EvaluateAndApplyBaseDamageMods(std::shared_ptr<DamageInstance> damageInstance);

	private:
};