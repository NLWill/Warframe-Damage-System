#include "src/DamagePipeline/HealthResistanceProcess/HealthResistanceProcess.h"
#include "src/Target/HealthType.h"
#include "src/Services/ServiceLocator.h"

void HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(DamageInstance *damageInstance)
{
	for (int j = 0; j < damageInstance->damageValues.size(); j++)
	{
		// ServiceLocator::GetLogger().Log("For damage type " + std::to_string(damageInstance->damageInstances[i]->damageData[j].damageType) + " the multiplier is " + std::to_string(damageInstance->target->healthType.GetDamageTypeModifier(damageInstance->damageInstances[i]->damageData[j].damageType)));
		damageInstance->damageValues[j] *= damageInstance->target->healthType.GetDamageTypeModifier(damageInstance->damageValues[j].damageType);
	}
}