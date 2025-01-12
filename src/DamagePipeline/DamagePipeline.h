#pragma once
#include "src/Mods/ModEffectBase.h"
#include "src/DamagePipeline/FireInstance.h"
#include <vector>
#include <tuple>

class DamagePipeline
{
public:
	static float EvaluateAndApplyModEffects(FireInstance *fireInstance, ModUpgradeType upgradeType, float baseValue);
	static std::tuple<float, float, float, float> CalculateModEffects(std::vector<ModEffectBase *> modEffects);
	static float RunDamagePipeline(Weapon &weapon, std::string attackName, Target &target);
};