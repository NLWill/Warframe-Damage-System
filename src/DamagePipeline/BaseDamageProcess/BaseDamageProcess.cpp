#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"

void BaseDamageProcess::EvaluateAndApplyBaseDamageMods(DamageInstance *damageInstance)
{	
	std::vector<ModEffectBase *> baseDamageModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_AMOUNT);
	
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, baseDamageModEffects);

	// Realistically, addToBaseBonus, multiplyBonus, flatAdditiveBonus should all be 0
	*damageInstance *= 1 + stackingMultiplyBonus;
}