#include "src/DamagePipeline/ModProcessingFunctions.h"

float ModProcessingFunctions::EvaluateAndApplyModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, float baseValue)
{
	// Fetch all mods that affect the ModUpgradeType
	auto modEffects = damageInstance->GetAllModEffects(upgradeType);

	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = CalculateModEffects(damageInstance, modEffects);

	// Apply the baseBonus
	baseValue += addToBaseBonus;
	// Apply the stacking_Multiply
	baseValue *= 1 + stackingMultiplyBonus;
	// Apply the multiplicativeBonus
	baseValue *= multiplyBonus;
	// Apply the flatAdditiveBonus
	baseValue += flatAdditiveBonus;

	// Handle any set operations and return if there are any
	for (size_t i = 0; i < modEffects.size(); i++)
	{
		if (modEffects[i]->GetModOperationType() == ModOperationType::SET)
		{
			baseValue = modEffects[i]->GetModValue(damageInstance);
		}
	}

	return baseValue;
}

std::tuple<float, float, float, float> ModProcessingFunctions::CalculateModEffects(std::shared_ptr<DamageInstance> damageInstance, std::vector<std::shared_ptr<IModEffect>> modEffects)
{
	float add_to_base_bonus = 0;
	float stacking_multiply_bonus = 0;
	float multiply_bonus = 1;
	float flat_additive_bonus = 0;

	for (size_t i = 0; i < modEffects.size(); i++)
	{
		float modValue = damageInstance->calculateAverageDamage ? modEffects[i]->GetAverageModValue(damageInstance) : modEffects[i]->GetModValue(damageInstance);
		switch (modEffects[i]->GetModOperationType())
		{
		case ModOperationType::ADD_TO_BASE_VALUE:
			add_to_base_bonus += modValue;
			break;
		case ModOperationType::STACKING_MULTIPLY:
			stacking_multiply_bonus += modValue;
			break;
		case ModOperationType::MULTIPLY:
			multiply_bonus *= (1 + modValue);
			break;
		case ModOperationType::ADD:
			flat_additive_bonus += modValue;
			break;
		default:
			break;
		}
	}

	return {add_to_base_bonus, stacking_multiply_bonus, multiply_bonus, flat_additive_bonus};
}
