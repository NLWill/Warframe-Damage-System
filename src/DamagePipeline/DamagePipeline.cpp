#include "src/DamagePipeline/DamagePipeline.h"
#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"
#include "src/DamagePipeline/NetworkQuantisationProcess/NetworkQuantisation.h"
#include "src/DamagePipeline/StatusChanceProcess/StatusChanceProcess.h"
#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/DamagePipeline/ExtraDamageMultipliers/ExtraDamageMultipliers.h"


float DamagePipeline::EvaluateAndApplyModEffects(FireInstance *fireInstance, ModUpgradeType upgradeType, float baseValue)
{
	// Fetch all mods that affect the crit chance
	std::vector<ModEffectBase *> modEffects = fireInstance->GetAllModEffects(upgradeType);

	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(modEffects);

	// Apply the baseBonus
	baseValue += addToBaseBonus;
	// Apply the stacking_Multiply
	baseValue *= 1 + stackingMultiplyBonus;
	// Apply the multiplicativeBonus
	baseValue *= multiplyBonus;
	// Apply the flatAdditiveBonus
	baseValue += flatAdditiveBonus;

	// Handle any set operations and return if there are any
	for (int i = 0; i < modEffects.size(); i++)
	{
		if (modEffects[i]->GetModOperationType() == ModOperationType::SET)
		{
			baseValue = modEffects[i]->GetModValue();
		}
	}

	return baseValue;
}

std::tuple<float, float, float, float> DamagePipeline::CalculateModEffects(std::vector<ModEffectBase *> modEffects)
{
	float add_to_base_bonus = 0;
	float stacking_multiply_bonus = 0;
	float multiply_bonus = 1;
	float flat_additive_bonus = 0;

	for (int i = 0; i < modEffects.size(); i++)
	{
		switch (modEffects[i]->GetModOperationType())
		{
		case ModOperationType::ADD_TO_BASE_VALUE:
			add_to_base_bonus += modEffects[i]->GetModValue();
			break;
		case ModOperationType::STACKING_MULTIPLY:
			stacking_multiply_bonus += modEffects[i]->GetModValue();
			break;
		case ModOperationType::MULTIPLY:
			multiply_bonus *= modEffects[i]->GetModValue();
			break;
		case ModOperationType::ADD:
			flat_additive_bonus += modEffects[i]->GetModValue();
			break;
		default:
			break;
		}
	}

	return {add_to_base_bonus, stacking_multiply_bonus, multiply_bonus, flat_additive_bonus};

}
float DamagePipeline::RunDamagePipeline(Weapon &weapon, std::string attackName, Target &target)
{
	FireInstance *fireInstance = new FireInstance(weapon, attackName, target);

	MultishotProcess::EvaluateMultishotMods(fireInstance);
	MultishotProcess::RollForMultishot(fireInstance);

	BaseDamageProcess::EvaluateAndApplyBaseDamageMods(fireInstance);

	NetworkQuantisation::AddElementsAndQuantise(fireInstance);

	StatusChanceProcess::EvaluateStatusChanceMods(fireInstance);
	StatusChanceProcess::EvaluateStatusDamageMods(fireInstance);
	StatusChanceProcess::RollForStatus(fireInstance);

	CriticalHitProcess::EvaluateCriticalChanceMods(fireInstance);
	CriticalHitProcess::EvaluateCriticalDamageMods(fireInstance);
	CriticalHitProcess::RollForCriticalHits(fireInstance);
	CriticalHitProcess::EvaluateCriticalTierMods(fireInstance);
	CriticalHitProcess::ApplyCriticalHitDamage(fireInstance);

	ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(fireInstance);

	return fireInstance->GetTotalDamage();
}