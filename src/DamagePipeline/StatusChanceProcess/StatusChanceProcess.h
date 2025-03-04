#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class StatusChanceProcess
{
public:
	static void EvaluateStatusChanceProcess(shared_ptr<DamageInstance> damageInstance);

private:
	static void EvaluateStatusChanceMods(shared_ptr<DamageInstance> damageInstance);
	static void EvaluateStatusDamageMods(shared_ptr<DamageInstance> damageInstance);
	static void EvaluateStatusDurationMods(shared_ptr<DamageInstance> damageInstance);
	static void RollForStatus(shared_ptr<DamageInstance> damageInstance);

	static void NormalRollForStatus(shared_ptr<DamageInstance> damageInstance, std::map<DamageType, float> &elementalWeights, float totalElementalWeighting);
	static void AverageRollForStatus(shared_ptr<DamageInstance> damageInstance, std::map<DamageType, float> &elementalWeights, float totalElementalWeighting);
};