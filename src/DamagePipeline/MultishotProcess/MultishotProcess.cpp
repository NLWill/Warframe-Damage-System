#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Services/ServiceLocator.h"

void MultishotProcess::EvaluateMultishotMods(FireInstance *fireInstance)
{
	float baseMultishot = fireInstance->weapon->data.attacks.at(fireInstance->attackName).multishot;
	fireInstance->moddedMultishot = DamagePipeline::EvaluateAndApplyModEffects(fireInstance, ModUpgradeType::WEAPON_MULTISHOT, baseMultishot);
}

void MultishotProcess::RollForMultishot(FireInstance *fireInstance)
{
	int rolledMultishot = ServiceLocator::GetRNG().WeightedFloorCeiling(fireInstance->moddedMultishot);
	for (int i = 0; i < rolledMultishot; i++)
	{
		fireInstance->damageInstances.push_back(new DamageInstance(fireInstance->weapon->data.attacks.at(fireInstance->attackName).attackData));
	}
}
