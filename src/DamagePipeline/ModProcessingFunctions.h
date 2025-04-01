#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Mods/ModUpgradeType.h"
#include "src/Mods/IModEffect.h"
#include <memory>
#include <vector>

class ModProcessingFunctions
{
public:
	/// @brief Find all mods which operate on the designated ModUpgradeType and apply them to the provided baseValue
	/// @param damageInstance The damage instance being processed
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @param baseValue The base value to which all mods apply
	/// @return The final value after all mods have been applied in order
	static float EvaluateAndApplyModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, float baseValue);

	/// @brief Iterate over all mods and find the total effects related to the ModUpgradeType for each ModOperationType
	/// @param damageInstance The damage instance being processed
	/// @param upgradeType The variable within the damage pipeline currently being evaluated
	/// @return A map of the values that must be applied to each ModOperationType. Existence of a ModOperatioType::SET entry suggests that a mod wants to override the value
	static std::map<ModOperationType, float> CalculateModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType);
};