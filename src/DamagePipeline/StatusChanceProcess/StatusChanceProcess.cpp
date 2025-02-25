#include "src/DamagePipeline/StatusChanceProcess/StatusChanceProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Services/ServiceLocator.h"

#define DEBUG_STATUS_PROCESS false

void StatusChanceProcess::EvaluateStatusChanceMods(DamageInstance *damageInstance)
{
	// Calculate the base status chance per pellet
	float baseStatusChance = damageInstance->damageData.statusChance / damageInstance->damageData.multishot;
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
	// Roll the number of statuses from status chance
	int numberOfStatuses = ServiceLocator::GetRNG().WeightedFloorCeiling(damageInstance->moddedStatusChance);
#if DEBUG_STATUS_PROCESS
	ServiceLocator::GetLogger().Log("Rolled number of statuses: " + std::to_string(numberOfStatuses));
#endif

	// Copy the elemental weights into a new map that may be modified
	auto elementalWeights{damageInstance->GetElementalWeights()};

	// If the target is immune to the status effect, set the weight of it to 0
	for (auto damageTypeWeightPair : elementalWeights)
	{
		for (ProcType pt : damageInstance->target->immuneStatusEffects)
		{
			if (ProcType::GetProcTypeFromElement(damageTypeWeightPair.first) == pt)
			{
				elementalWeights[damageTypeWeightPair.first] = 0;
			}
		}
	}

	float totalElementalWeighting = 0;
	for (auto damageTypeWeightPair : elementalWeights)
	{
		totalElementalWeighting += damageTypeWeightPair.second;
	}

	for (int j = 0; j < numberOfStatuses; j++)
	{
		float randomNumber = ServiceLocator::GetRNG().RandomFloat(0, totalElementalWeighting);

		float counter = 0;
		for (auto damageTypeWeightPair : elementalWeights)
		{
			counter += damageTypeWeightPair.second;
			if (counter > randomNumber)
			{
#if DEBUG_STATUS_PROCESS
				ServiceLocator::GetLogger().Log("Applying status effect: " + ProcType::GetProcTypeFromElement(damageTypeWeightPair.first).ToString());
#endif
				damageInstance->AddStatusEffect(ProcType::GetProcTypeFromElement(damageTypeWeightPair.first));
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
