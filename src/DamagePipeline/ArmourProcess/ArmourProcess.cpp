#include "src/DamagePipeline/ArmourProcess/ArmourProcess.h"

void ArmourProcess::EvaluateAndApplyArmourDamageReduction(DamageInstance *damageInstance)
{
	float armour = damageInstance->target->GetArmour();
	float damageReductionMultiplier = 1 - armour / (300 + armour);
	*damageInstance *= damageReductionMultiplier;
}