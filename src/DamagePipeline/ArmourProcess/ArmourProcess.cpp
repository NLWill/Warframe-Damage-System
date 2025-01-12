#include "src/DamagePipeline/ArmourProcess/ArmourProcess.h"

void ArmourProcess::EvaluateAndApplyArmourDamageReduction(FireInstance *fireInstance)
{
	float armour = fireInstance->target->currentArmour;
	float damageReductionMultiplier = 1 - armour / (300 + armour);
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		*(fireInstance->damageInstances[i]) *= damageReductionMultiplier;
	}
}