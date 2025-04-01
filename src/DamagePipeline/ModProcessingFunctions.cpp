#include "src/DamagePipeline/ModProcessingFunctions.h"
#include <iostream>

float ModProcessingFunctions::EvaluateAndApplyModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, float baseValue)
{
	std::map<ModOperationType, float> modEffectValues = CalculateModEffects(damageInstance, upgradeType);

	// Apply the add to base bonus
	baseValue += modEffectValues[ModOperationType::ADD_TO_BASE_VALUE];
	// Apply the stacking multiply bonus
	baseValue *= 1 + modEffectValues[ModOperationType::STACKING_MULTIPLY];
	// Apply the pure multiply bonus
	baseValue *= modEffectValues[ModOperationType::MULTIPLY];
	// Apply the flat additive bonus
	baseValue += modEffectValues[ModOperationType::ADD];

	// Check whether any mods tried to set the value and override the baseValue if so
	if (modEffectValues.contains(ModOperationType::SET))
	{
		baseValue = modEffectValues[ModOperationType::SET];
	}

	return baseValue;
}

std::map<ModOperationType, float> ModProcessingFunctions::CalculateModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType)
{
	std::map<ModOperationType, float> modEffectValues;
	modEffectValues[ModOperationType::ADD_TO_BASE_VALUE] = 0;
	modEffectValues[ModOperationType::STACKING_MULTIPLY] = 0;
	modEffectValues[ModOperationType::MULTIPLY] = 1;
	modEffectValues[ModOperationType::ADD] = 0;

	DamageInstance::EvaluateModEffects(damageInstance, upgradeType, modEffectValues);

	return modEffectValues;
}
