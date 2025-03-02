#pragma once
#include "src/Mods/ModEffectBase.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Target/Target.h"
#include <vector>
#include <tuple>

class DamagePipeline
{
public:
	static float EvaluateAndApplyModEffects(DamageInstance *damageInstance, ModUpgradeType upgradeType, float baseValue);
	static std::tuple<float, float, float, float> CalculateModEffects(DamageInstance *damageInstance, std::vector<ModEffectBase *> modEffects);
	static std::pair<float, float> RunDamagePipeline(DamageInstance *damageInstance);
	static std::pair<float, float> RunAverageDamagePipeline(DamageInstance *damageInstance);

	private:
	static std::pair<float, float> DealDamageToTarget(DamageInstance *damageInstance);
};