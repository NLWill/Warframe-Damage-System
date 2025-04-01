#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

#define DEBUG_BASE_DAMAGE_PROCESS false
#if DEBUG_BASE_DAMAGE_PROCESS
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#endif

void BaseDamageProcess::EvaluateAndApplyBaseDamageMods(std::shared_ptr<DamageInstance> damageInstance)
{
	// Find all mods that affect the base damage process
	std::map<ModOperationType, float> modEffectValues = ModProcessingFunctions::CalculateModEffects(damageInstance, ModUpgradeType::WEAPON_DAMAGE_AMOUNT);

#if DEBUG_BASE_DAMAGE_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Processing Base Damage Bonus");
	ServiceLocator::GetService<ILogService>()->Log("addToBaseBonus = " + std::to_string(modEffectValues[ModOperationType::ADD_TO_BASE_VALUE]));
	ServiceLocator::GetService<ILogService>()->Log("stackingMultiplyBonus = " + std::to_string(modEffectValues[ModOperationType::STACKING_MULTIPLY]));
	ServiceLocator::GetService<ILogService>()->Log("multiplyBonus = " + std::to_string(modEffectValues[ModOperationType::MULTIPLY]));
	ServiceLocator::GetService<ILogService>()->Log("flatAdditiveBonus = " + std::to_string(modEffectValues[ModOperationType::ADD]));
#endif

	// Realistically, multiplyBonus, flatAdditiveBonus should be 0
	// addToBaseBonus is akin to the incarnon evolutions +20 damage
	if (modEffectValues[ModOperationType::ADD_TO_BASE_VALUE] != 0)
	{
		float baseWeaponDamage = damageInstance->GetTotalDamage();
		float buffedWeaponDamage = baseWeaponDamage + modEffectValues[ModOperationType::ADD_TO_BASE_VALUE];
		*damageInstance *= buffedWeaponDamage / baseWeaponDamage;
	}

	// Apply the stackingMultiplyBonus of the Base Damage Mods
	*damageInstance *= 1 + modEffectValues[ModOperationType::STACKING_MULTIPLY];
	*damageInstance *= modEffectValues[ModOperationType::MULTIPLY];
}