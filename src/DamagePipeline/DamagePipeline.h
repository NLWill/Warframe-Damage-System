#pragma once
#include "src/Mods/IModEffect.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Target/Target.h"
#include <vector>
#include <tuple>

class DamagePipeline
{
public:
	/// @brief Run the provided DamageInstance through the entire damage pipeline from trigger pull to health loss on the target
	/// @param damageInstance The DamageInstance dealing damage to the target
	/// @return A pair of floats for the total direct damage dealt to the target as well as the DPS from status effects
	static std::pair<float, float> RunDamagePipeline(std::shared_ptr<DamageInstance> damageInstance);

	/// @brief Calculate the average damage dealt by a damage instance by running the provided DamageInstance through the entire damage pipeline from trigger pull to health loss on the target
	/// @param damageInstance The DamageInstance dealing damage to the target
	/// @return A pair of floats for the average direct damage dealt to the target as well as the average DPS from status effects
	static std::pair<float, float> RunAverageDamagePipeline(std::shared_ptr<DamageInstance> damageInstance);

private:
	/// @brief The sub-structure of the DamagePipeline responsible for handling base damage bonuses, elements, and other similar multipliers
	/// @param damageInstance The DamageInstance dealing damage to the target
	static void ApplyBonusesAtTriggerPull(std::shared_ptr<DamageInstance> damageInstance);

	/// @brief The sub-structure of the DamagePipeline responsible for handling effects that require the target to be hit, such as condition overload, critical hits, and hitzones
	/// @param damageInstance The DamageInstance dealing damage to the target
	static void ApplyOnHitBonuses(std::shared_ptr<DamageInstance> damageInstance);
	
	/// @brief A sub-structure of the DamagePipeline responsible for handling headshot bonuses, status application, damage resistances, and armour
	/// This operates for both the normal DamagePipeline as well as the Average DamagePipeline
	/// @param damageInstance The DamageInstance dealing damage to the target
	/// @return A pair of floats for the total direct damage dealt to the target as well as the DPS from status effects
	static std::pair<float, float> DealDamageToTarget(std::shared_ptr<DamageInstance> damageInstance);
};