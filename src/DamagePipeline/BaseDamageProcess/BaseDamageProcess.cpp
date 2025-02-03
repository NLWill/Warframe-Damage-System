#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"

void BaseDamageProcess::EvaluateAndApplyBaseDamageMods(DamageInstance *damageInstance)
{
	std::vector<ModEffectBase *> baseDamageModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_AMOUNT);

	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, baseDamageModEffects);

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
}