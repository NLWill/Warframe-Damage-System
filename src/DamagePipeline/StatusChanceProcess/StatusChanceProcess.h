#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class StatusChanceProcess
{
public:
	static void EvaluateStatusChanceProcess(std::shared_ptr<DamageInstance> damageInstance);

private:
	static void EvaluateStatusChanceMods(std::shared_ptr<DamageInstance> damageInstance);
	static void EvaluateStatusDamageMods(std::shared_ptr<DamageInstance> damageInstance);
	static void EvaluateStatusDurationMods(std::shared_ptr<DamageInstance> damageInstance);
	static void RollForStatus(std::shared_ptr<DamageInstance> damageInstance);

	static void NormalRollForStatus(std::shared_ptr<DamageInstance> damageInstance, std::map<DamageType, float> &elementalWeights, float totalElementalWeighting);
	static void AverageRollForStatus(std::shared_ptr<DamageInstance> damageInstance, std::map<DamageType, float> &elementalWeights, float totalElementalWeighting);
};