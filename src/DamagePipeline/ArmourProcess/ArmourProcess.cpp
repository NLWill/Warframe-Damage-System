#include "src/DamagePipeline/ArmourProcess/ArmourProcess.h"
#include <cmath>

#define DEBUG_ARMOUR_PROCESS false
#if DEBUG_ARMOUR_PROCESS
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#endif

void ArmourProcess::EvaluateAndApplyArmourDamageReduction(std::shared_ptr<DamageInstance> damageInstance)
{
	float armour = damageInstance->target->GetArmour();
	//float tennoDRMultiplier = 1 - armour / (300 + armour);
	float enemyDRMultiplier = 1 - 0.9 * std::sqrt(armour / 2700);
	float damageReductionMultiplier = enemyDRMultiplier;

	for (size_t i = 0; i < damageInstance->damageValues.size(); i++)
	{
		// Allow true damage to bypass armour
		switch (damageInstance->damageValues[i].damageType){
			case DamageType::DT_TRUE:
			break;
			default:
			damageInstance->damageValues[i] *= damageReductionMultiplier;
			break;
		}

		// Bizarrely the armour process ensures that each damage type cannot be lower than 1 damage each
		if (damageInstance->damageValues[i].value < 1){
			damageInstance->damageValues[i].value = 1;
		}
	}

#if DEBUG_ARMOUR_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Armour Process applying a DR multiplier of " + std::to_string(damageReductionMultiplier));
#endif
}