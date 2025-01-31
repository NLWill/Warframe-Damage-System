#include "src/DamagePipeline/ExtraDamageMultipliers/ExtraDamageMultipliers.h"
#include "src/DamagePipeline/DamagePipeline.h"

void ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(DamageInstance *damageInstance)
{
	std::vector<ModEffectBase *> multiplierModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_MULTIPLIER);
	
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, multiplierModEffects);

	// Realistically, addToBaseBonus, stackingMultiplyBonus, flatAdditiveBonus should all be 0
	*damageInstance *= multiplyBonus;
}