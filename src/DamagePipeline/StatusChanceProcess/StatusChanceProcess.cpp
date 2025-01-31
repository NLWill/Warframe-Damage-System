#include "src/DamagePipeline/StatusChanceProcess/StatusChanceProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Services/ServiceLocator.h"

void StatusChanceProcess::EvaluateStatusChanceMods(DamageInstance *damageInstance)
{
	float baseStatusChance = damageInstance->weapon->data.attacks.at(damageInstance->attackName).statusChance;
	damageInstance->moddedStatusChance = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_STATUS_CHANCE, baseStatusChance);
}

void StatusChanceProcess::EvaluateStatusDamageMods(DamageInstance *damageInstance)
{
	damageInstance->moddedStatusDamageMultiplier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_STATUS_DAMAGE, 1);
}

void StatusChanceProcess::RollForStatus(DamageInstance *damageInstance)
{
	float totalDamage = damageInstance->GetTotalDamage();

	// Roll the number of statuses from status chance
	int numberOfStatuses = ServiceLocator::GetRNG().WeightedFloorCeiling(damageInstance->moddedStatusChance);
	ServiceLocator::GetLogger().Log("Rolled number of statuses: " + std::to_string(numberOfStatuses));

	for (int j = 0; j < numberOfStatuses; j++)
	{
		float randomNumber = ServiceLocator::GetRNG().RandomFloat(0, totalDamage);

		float counter = 0;
		for (int k = 0; k < damageInstance->damageData.size(); k++)
		{
			counter += damageInstance->damageData[k].value;
			if (counter > randomNumber)
			{
				ServiceLocator::GetLogger().Log("Applying status effect: " + StatusEffect::GetStatusEffectFromElement(damageInstance->damageData[k].damageType).ToString());
				damageInstance->AddStatusEffect(StatusEffect::GetStatusEffectFromElement(damageInstance->damageData[k].damageType));
				break;
			}
		}
	}

	// Add forced procs innate from the weapon
	for (StatusEffect forcedProc : damageInstance->weapon->data.attacks.at(damageInstance->attackName).forcedProcs)
	{
		ServiceLocator::GetLogger().Log("Applying forced status effect: " + forcedProc.ToString());
		damageInstance->AddStatusEffect(forcedProc);
	}
}
