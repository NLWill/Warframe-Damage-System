#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Services/ServiceLocator.h"

void MultishotProcess::EvaluateMultishotMods(FireInstance *fireInstance)
{
	auto tempDamageInstance = new DamageInstance();
	tempDamageInstance->weapon = fireInstance->weapon;
	tempDamageInstance->attackName = fireInstance->attackName;

	float baseMultishot = fireInstance->weapon->weaponData.firingModes.at(fireInstance->attackName).attackData.damageData.multishot;
	fireInstance->moddedMultishot = DamagePipeline::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_MULTISHOT, baseMultishot);

	delete tempDamageInstance;
}

int MultishotProcess::RollForMultishot(FireInstance *fireInstance)
{
	int rolledMultishot = ServiceLocator::GetRNG().WeightedFloorCeiling(fireInstance->moddedMultishot);
	return rolledMultishot;
}
