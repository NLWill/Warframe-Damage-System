#include "src/DamagePipeline/StatusChanceProcess/StatusChanceProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Services/ServiceLocator.h"

void StatusChanceProcess::EvaluateStatusChanceMods(FireInstance *fireInstance)
{
	float baseStatusChance = fireInstance->weapon->data.attacks.at(fireInstance->attackName).statusChance;
	fireInstance->moddedStatusChance = DamagePipeline::EvaluateAndApplyModEffects(fireInstance, ModUpgradeType::WEAPON_STATUS_CHANCE, baseStatusChance);
}

void StatusChanceProcess::EvaluateStatusDamageMods(FireInstance *fireInstance)
{
	fireInstance->moddedStatusDamageMultiplier = DamagePipeline::EvaluateAndApplyModEffects(fireInstance, ModUpgradeType::WEAPON_STATUS_DAMAGE, 1);
}

void StatusChanceProcess::RollForStatus(FireInstance *fireInstance)
{
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		float totalDamage = fireInstance->damageInstances[i]->GetTotalDamage();

		int numberOfStatuses = ServiceLocator::GetRNG().WeightedFloorCeiling(fireInstance->moddedStatusChance);
		ServiceLocator::GetLogger().Log("Rolled number of statuses: " + std::to_string(numberOfStatuses));

		for (int j = 0; j < numberOfStatuses; j++)
		{
			float randomNumber = ServiceLocator::GetRNG().RandomFloat(0, totalDamage);

			float counter = 0;
			for (int k = 0; k < fireInstance->damageInstances[i]->damageData.size(); k++)
			{
				counter += fireInstance->damageInstances[i]->damageData[k].value;
				if (counter > randomNumber)
				{
					ServiceLocator::GetLogger().Log("Applying status effect: " + StatusEffect::GetStatusEffectFromElement(fireInstance->damageInstances[i]->damageData[k].damageType).ToString());
					fireInstance->damageInstances[i]->AddStatusEffect(StatusEffect::GetStatusEffectFromElement(fireInstance->damageInstances[i]->damageData[k].damageType));
					break;
				}
			}
		}
	}
}
