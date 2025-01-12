#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"

void BaseDamageProcess::EvaluateAndApplyBaseDamageMods(FireInstance *fireInstance)
{	
	std::vector<ModEffectBase *> baseDamageModEffects = fireInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_AMOUNT);
	
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(baseDamageModEffects);

	// Realistically, addToBaseBonus, multiplyBonus, flatAdditiveBonus should all be 0
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		*(fireInstance->damageInstances[i]) *= 1 + stackingMultiplyBonus;
	}
	
}