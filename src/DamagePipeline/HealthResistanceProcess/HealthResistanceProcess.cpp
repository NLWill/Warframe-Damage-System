#include "src/DamagePipeline/HealthResistanceProcess/HealthResistanceProcess.h"
#include "src/Target/HealthType.h"

void HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(FireInstance *fireInstance)
{
	float armour = fireInstance->target->GetArmour();
	float damageReductionMultiplier = 1 - armour / (300 + armour);
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		for (int j = 0; j < fireInstance->damageInstances[i]->damageData.size(); j++)
		{
			fireInstance->damageInstances[i]->damageData[j] *= fireInstance->target->healthType.GetDamageTypeModifier(fireInstance->damageInstances[i]->damageData[j].damageType);
		}
		
		*(fireInstance->damageInstances[i]) *= damageReductionMultiplier;
	}
}