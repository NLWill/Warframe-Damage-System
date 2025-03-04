#include "src/DamagePipeline/HealthResistanceProcess/HealthResistanceProcess.h"
#include "src/Target/HealthType.h"

#define DEBUG_HEALTH_RESISTANCE_PROCESS false
#if DEBUG_HEALTH_RESISTANCE_PROCESS
#include "src/Services/ServiceLocator.h"
#endif

void HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(shared_ptr<DamageInstance> damageInstance)
{
	for (size_t j = 0; j < damageInstance->damageValues.size(); j++)
	{
#if DEBUG_HEALTH_RESISTANCE_PROCESS
		ServiceLocator::GetLogger().Log("For damage type " + std::to_string(damageInstance->damageInstances[i]->damageData[j].damageType) + " the multiplier is " + std::to_string(damageInstance->target->healthType.GetDamageTypeModifier(damageInstance->damageInstances[i]->damageData[j].damageType)));
#endif
		damageInstance->damageValues[j] *= damageInstance->target->healthType.GetDamageTypeModifier(damageInstance->damageValues[j].damageType);
	}
}