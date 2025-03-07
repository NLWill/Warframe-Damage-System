#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Mods/ModUpgradeType.h"
#include "src/Mods/IModEffect.h"
#include <memory>
#include <vector>

class ModProcessingFunctions{
	public:	

	/// @brief Find all mods which operate on the designated ModUpgradeType and apply them to the provided baseValue
	/// @param damageInstance
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @param baseValue The base value to which all mods apply
	/// @return The final value after all mods have been applied in order
	static float EvaluateAndApplyModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, float baseValue);

	/// @brief Iterate over all mods and conglomerate their effects into their order of operations
	/// @param damageInstance
	/// @param modEffects Vector of all mod effects being queried
	/// @return A tuple of form {add_to_base_bonus, stacking_multiply_bonus, multiply_bonus, flat_additive_bonus}
	static std::tuple<float, float, float, float> CalculateModEffects(std::shared_ptr<DamageInstance> damageInstance, std::vector<std::shared_ptr<IModEffect>> modEffects);
};