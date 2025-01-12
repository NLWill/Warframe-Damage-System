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

		float randomNumber = ServiceLocator::GetRNG().RandomFloat(0, totalDamage);

		float counter = 0;
		for (int j = 0; j < fireInstance->damageInstances[i]->damageData.size(); j++)
		{
			counter += fireInstance->damageInstances[i]->damageData[j].value;
			if (counter > randomNumber)
			{
				fireInstance->damageInstances[i]->AddStatusEffect(StatusEffect::GetStatusEffectFromElement(fireInstance->damageInstances[i]->damageData[j].damageType));
			}
		}
	}
}
