#include "src/DamagePipeline/ArmourProcess/ArmourProcess.h"

#define DEBUG_ARMOUR_PROCESS false
#if DEBUG_ARMOUR_PROCESS
#include "src/Services/ServiceLocator.h"
#endif

void ArmourProcess::EvaluateAndApplyArmourDamageReduction(DamageInstance *damageInstance)
{
	float armour = damageInstance->target->GetArmour();
	float damageReductionMultiplier = 1 - armour / (300 + armour);
	*damageInstance *= damageReductionMultiplier;

	#if DEBUG_ARMOUR_PROCESS
	ServiceLocator::GetLogger().Log("Armour Process applying a DR multiplier of " + std::to_string(damageReductionMultiplier));
	#endif
	
}