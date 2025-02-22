#include "src/DamagePipeline/StatusChanceProcess/StatusChanceProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Services/ServiceLocator.h"
#include "StatusChanceProcess.h"

#define DEBUG_STATUS_PROCESS false

void StatusChanceProcess::EvaluateStatusChanceMods(DamageInstance *damageInstance)
{
	float baseStatusChance = damageInstance->damageData.statusChance;
	damageInstance->moddedStatusChance = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_STATUS_CHANCE, baseStatusChance);
}

void StatusChanceProcess::EvaluateStatusDamageMods(DamageInstance *damageInstance)
{
	damageInstance->moddedStatusDamageMultiplier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_STATUS_DAMAGE, 1);
}

void StatusChanceProcess::EvaluateStatusDurationMods(DamageInstance *damageInstance)
{
	damageInstance->moddedStatusDurationMultiplier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_STATUS_DURATION, 1);
}

void StatusChanceProcess::RollForStatus(DamageInstance *damageInstance)
{
	float totalDamage = damageInstance->GetTotalDamage();

	// Roll the number of statuses from status chance
	int numberOfStatuses = ServiceLocator::GetRNG().WeightedFloorCeiling(damageInstance->moddedStatusChance);
	#if DEBUG_STATUS_PROCESS
	ServiceLocator::GetLogger().Log("Rolled number of statuses: " + std::to_string(numberOfStatuses));
	#endif

	for (int j = 0; j < numberOfStatuses; j++)
	{
		float randomNumber = ServiceLocator::GetRNG().RandomFloat(0, totalDamage);

		float counter = 0;
		for (int k = 0; k < damageInstance->damageValues.size(); k++)
		{
			counter += damageInstance->damageValues[k].value;
			if (counter > randomNumber)
			{
				#if DEBUG_STATUS_PROCESS
				ServiceLocator::GetLogger().Log("Applying status effect: " + ProcType::GetProcTypeFromElement(damageInstance->damageData[k].damageType).ToString());
				#endif
				damageInstance->AddStatusEffect(ProcType::GetProcTypeFromElement(damageInstance->damageValues[k].damageType));
				break;
			}
		}
	}

	// Add forced procs innate from the weapon
	for (ProcType forcedProc : damageInstance->damageData.forcedProcs)
	{
		#if DEBUG_STATUS_PROCESS
		ServiceLocator::GetLogger().Log("Applying forced status effect: " + forcedProc.ToString());
		#endif
		damageInstance->AddStatusEffect(forcedProc);
	}
}
