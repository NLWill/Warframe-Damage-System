#include "src/DamagePipeline/ExtraDamageMultipliers/ExtraDamageMultipliers.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

void ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(std::shared_ptr<DamageInstance> damageInstance)
{
	auto multiplierModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_MULTIPLIER);
	
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = ModProcessingFunctions::CalculateModEffects(damageInstance, multiplierModEffects);

	// Realistically, addToBaseBonus, stackingMultiplyBonus, flatAdditiveBonus should all be 0
	*damageInstance *= multiplyBonus;
}