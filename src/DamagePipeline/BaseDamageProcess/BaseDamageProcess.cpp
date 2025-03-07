#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

#define DEBUG_BASE_DAMAGE_PROCESS false
#if DEBUG_BASE_DAMAGE_PROCESS
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#endif

void BaseDamageProcess::EvaluateAndApplyBaseDamageMods(std::shared_ptr<DamageInstance> damageInstance)
{
	auto baseDamageModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_AMOUNT);

	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = ModProcessingFunctions::CalculateModEffects(damageInstance, baseDamageModEffects);

#if DEBUG_BASE_DAMAGE_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Processing Base Damage Bonus");
	ServiceLocator::GetService<ILogService>()->Log("addToBaseBonus = " + std::to_string(addToBaseBonus));
	ServiceLocator::GetService<ILogService>()->Log("stackingMultiplyBonus = " + std::to_string(stackingMultiplyBonus));
	ServiceLocator::GetService<ILogService>()->Log("multiplyBonus = " + std::to_string(multiplyBonus));
	ServiceLocator::GetService<ILogService>()->Log("flatAdditiveBonus = " + std::to_string(flatAdditiveBonus));
#endif

	// Realistically, multiplyBonus, flatAdditiveBonus should be 0
	// addToBaseBonus is akin to the incarnon evolutions +20 damage
	if (addToBaseBonus != 0)
	{
		float baseWeaponDamage = damageInstance->GetTotalDamage();
		float buffedWeaponDamage = baseWeaponDamage + addToBaseBonus;
		*damageInstance *= buffedWeaponDamage / baseWeaponDamage;
	}

	// Apply the stackingMultiplyBonus of the Base Damage Mods
	*damageInstance *= 1 + stackingMultiplyBonus;
	*damageInstance *= multiplyBonus;
}