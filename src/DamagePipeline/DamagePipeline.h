#pragma once
#include "src/Mods/ModEffectBase.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Target/Target.h"
#include <vector>
#include <tuple>

class DamagePipeline
{
public:
	static float EvaluateAndApplyModEffects(DamageInstance *damageInstance, ModUpgradeType upgradeType, float baseValue, bool averageCalculation = false);
	static std::tuple<float, float, float, float> CalculateModEffects(DamageInstance *damageInstance, std::vector<ModEffectBase *> modEffects, bool averageCalculation = false);
	static float RunDamagePipeline(DamageInstance *damageInstance);
	static float RunAverageDamagePipeline(DamageInstance *damageInstance);

	private:
};