#include "src/DamagePipeline/HealthResistanceProcess/HealthResistanceProcess.h"
#include "src/Target/HealthType.h"
#include "src/Services/ServiceLocator.h"

void HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(FireInstance *fireInstance)
{
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		for (int j = 0; j < fireInstance->damageInstances[i]->damageData.size(); j++)
		{
			//ServiceLocator::GetLogger().Log("For damage type " + std::to_string(fireInstance->damageInstances[i]->damageData[j].damageType) + " the multiplier is " + std::to_string(fireInstance->target->healthType.GetDamageTypeModifier(fireInstance->damageInstances[i]->damageData[j].damageType)));
			fireInstance->damageInstances[i]->damageData[j] *= fireInstance->target->healthType.GetDamageTypeModifier(fireInstance->damageInstances[i]->damageData[j].damageType);
		}
	}
}