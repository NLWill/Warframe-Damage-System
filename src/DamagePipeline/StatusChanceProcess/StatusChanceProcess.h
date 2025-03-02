#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class StatusChanceProcess
{
public:
	static void EvaluateStatusChanceMods(DamageInstance *damageInstance);
	static void EvaluateStatusDamageMods(DamageInstance *damageInstance);
	static void EvaluateStatusDurationMods(DamageInstance *damageInstance);
	static void RollForStatus(DamageInstance *damageInstance);

private:
static void NormalRollForStatus(DamageInstance *damageInstance, std::map<DamageType, float> &elementalWeights, float totalElementalWeighting);
static void AverageRollForStatus(DamageInstance *damageInstance, std::map<DamageType, float> &elementalWeights, float totalElementalWeighting);
};