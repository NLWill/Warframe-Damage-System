#include "src/DamagePipeline/ExtraDamageMultipliers/ExtraDamageMultipliers.h"
#include "src/DamagePipeline/DamagePipeline.h"

void ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(FireInstance *fireInstance)
{
	std::vector<ModEffectBase *> multiplierModEffects = fireInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_MULTIPLIER);
	
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(multiplierModEffects);

	// Realistically, addToBaseBonus, stackingMultiplyBonus, flatAdditiveBonus should all be 0
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		*(fireInstance->damageInstances[i]) *= multiplyBonus;
	}
}