#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"

#define DEBUG_MULTISHOT_PROCESS false
#if DEBUG_MULTISHOT_PROCESS
#include "src/Services/ServiceLocator.h"
#endif

void MultishotProcess::EvaluateMultishotMods(FireInstance *fireInstance)
{
	auto tempDamageInstance = new DamageInstance();
	tempDamageInstance->weapon = fireInstance->weapon;
	tempDamageInstance->attackName = fireInstance->attackName;

	float baseMultishot = fireInstance->weapon->weaponData.firingModes.at(fireInstance->attackName).attackData.damageData.multishot;
	fireInstance->moddedMultishot = DamagePipeline::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_MULTISHOT, baseMultishot);

#if DEBUG_MULTISHOT_PROCESS
	ServiceLocator::GetLogger().Log("Modded multishot = " + std::to_string(fireInstance->moddedMultishot));
#endif

	delete tempDamageInstance;
}

int MultishotProcess::RollForMultishot(FireInstance *fireInstance)
{
	int rolledMultishot = ServiceLocator::GetRNG().WeightedFloorCeiling(fireInstance->moddedMultishot);
#if DEBUG_MULTISHOT_PROCESS
	ServiceLocator::GetLogger().Log("Rolled a multishot of " + std::to_string(rolledMultishot));
#endif
	return rolledMultishot;
}
