#pragma once
#include "src/Mods/ModEffectBase.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Target/Target.h"
#include <vector>
#include <tuple>

class DamagePipeline
{
public:
	static float EvaluateAndApplyModEffects(shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, float baseValue);
	static std::tuple<float, float, float, float> CalculateModEffects(shared_ptr<DamageInstance> damageInstance, std::vector<shared_ptr<ModEffectBase>> modEffects);
	static std::pair<float, float> RunDamagePipeline(shared_ptr<DamageInstance> damageInstance);
	static std::pair<float, float> RunAverageDamagePipeline(shared_ptr<DamageInstance> damageInstance);

	private:
	static std::pair<float, float> DealDamageToTarget(shared_ptr<DamageInstance> damageInstance);
};