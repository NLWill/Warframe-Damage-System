#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/Services/ServiceLocator.h"
#include "src/Services/RNG/IRNGService.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

#define DEBUG_MULTISHOT_PROCESS false
#if DEBUG_MULTISHOT_PROCESS
#include "src/Services/Logging/ILogService.h"
#endif

void MultishotProcess::EvaluateMultishotMods(std::shared_ptr<FireInstance> fireInstance)
{
#if DEBUG_MULTISHOT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Entered EvaluateMultishotMods");
#endif
	auto tempDamageInstance = std::make_shared<DamageInstance>(fireInstance->weapon, fireInstance->attackName, DamageData(), std::make_shared<Target>(), "Body");
	#if DEBUG_MULTISHOT_PROCESS
		ServiceLocator::GetService<ILogService>()->Log("Created damage instance");
	#endif

	float baseMultishot = fireInstance->weapon->weaponData.firingModes.at(fireInstance->attackName).attackData.damageData.multishot;
	fireInstance->moddedMultishot = ModProcessingFunctions::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_FIRE_ITERATIONS, baseMultishot);

#if DEBUG_MULTISHOT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Modded multishot = " + std::to_string(fireInstance->moddedMultishot));
#endif
}

int MultishotProcess::RollForMultishot(std::shared_ptr<FireInstance> fireInstance)
{
	int rolledMultishot = ServiceLocator::GetService<IRNGService>()->WeightedFloorCeiling(fireInstance->moddedMultishot);
#if DEBUG_MULTISHOT_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Rolled a multishot of " + std::to_string(rolledMultishot));
#endif
	return rolledMultishot;
}
