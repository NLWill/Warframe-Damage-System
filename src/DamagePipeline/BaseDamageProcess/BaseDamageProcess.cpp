#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"

#define DEBUG_BASE_DAMAGE_PROCESS false

void BaseDamageProcess::EvaluateAndApplyBaseDamageMods(DamageInstance *damageInstance, bool averageDamageCalculation)
{
	std::vector<ModEffectBase *> baseDamageModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_AMOUNT);

	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, baseDamageModEffects, averageDamageCalculation);

#if DEBUG_BASE_DAMAGE_PROCESS
	ServiceLocator::GetLogger().Log("Processing Base Damage Bonus");
	ServiceLocator::GetLogger().Log("addToBaseBonus = " + std::to_string(addToBaseBonus));
	ServiceLocator::GetLogger().Log("stackingMultiplyBonus = " + std::to_string(stackingMultiplyBonus));
	ServiceLocator::GetLogger().Log("multiplyBonus = " + std::to_string(multiplyBonus));
	ServiceLocator::GetLogger().Log("flatAdditiveBonus = " + std::to_string(flatAdditiveBonus));
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