#pragma once
#include "src/Mods/IModEffect.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Target/Target.h"
#include <vector>
#include <tuple>

class DamagePipeline
{
public:
	static float EvaluateAndApplyModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, float baseValue);
	static std::tuple<float, float, float, float> CalculateModEffects(std::shared_ptr<DamageInstance> damageInstance, std::vector<std::shared_ptr<IModEffect>> modEffects);
	static std::pair<float, float> RunDamagePipeline(std::shared_ptr<DamageInstance> damageInstance);
	static std::pair<float, float> RunAverageDamagePipeline(std::shared_ptr<DamageInstance> damageInstance);

	private:
	static std::pair<float, float> DealDamageToTarget(std::shared_ptr<DamageInstance> damageInstance);
};