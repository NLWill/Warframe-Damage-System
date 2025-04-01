#include "src/DamagePipeline/ExtraDamageMultipliers/ExtraDamageMultipliers.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

void ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(std::shared_ptr<DamageInstance> damageInstance)
{
	std::map<ModOperationType, float> modEffectValues = ModProcessingFunctions::CalculateModEffects(damageInstance, ModUpgradeType::WEAPON_DAMAGE_MULTIPLIER);

	// Realistically, addToBaseBonus, stackingMultiplyBonus, flatAdditiveBonus should all be 0, but apply anyway for rigour
	*damageInstance *= 1 + modEffectValues[ModOperationType::STACKING_MULTIPLY];
	*damageInstance *= modEffectValues[ModOperationType::MULTIPLY];
}