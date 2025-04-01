#include "src/DamagePipeline/ConditionOverloadProcess/ConditionOverloadProcess.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

#define DEBUG_CONDITION_OVERLOAD_PROCESS false
#if DEBUG_CONDITION_OVERLOAD_PROCESS
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#endif

void ConditionOverloadProcess::EvaluateAndApplyConditionOverloadDamage(std::shared_ptr<DamageInstance> damageInstance)
{
	// Get the base damage of the attack before any mods
	float baseDamageOfWeapon = damageInstance->damageData.damageTotal;
#if DEBUG_CONDITION_OVERLOAD_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Got base damage of weapon: " + std::to_string(baseDamageOfWeapon));
#endif

	// Calculate the mod effects for each ModOperationType
	std::map<ModOperationType, float> modEffectValues = ModProcessingFunctions::CalculateModEffects(damageInstance, ModUpgradeType::WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE);
#if DEBUG_CONDITION_OVERLOAD_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Stacking multiply bonus: " + std::to_string(modEffectValues[ModOperationType::STACKING_MULTIPLY]));
#endif

	
	// Calculate the bonus base damage gained from CO effects
	float bonusDamage = baseDamageOfWeapon * (modEffectValues[ModOperationType::STACKING_MULTIPLY]);
#if DEBUG_CONDITION_OVERLOAD_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Bonus damage to add = " + std::to_string(bonusDamage));
#endif

// Determine the new base damage of the weapon from the current base damage value (including WEAPON_DAMAGE_AMOUNT bonuses) and adding the bonus damage from this.
// baseDamageOfWeapon * (normal WEAPON_DAMAGE_AMOUT bonuses) + baseDamageOfWeapon * (WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE bonuses).
// There is a fundamental flaw in this process, that is identical within the game.
// Some other extra multipliers (such as Mirage's Eclipse) only apply to the WEAPON_DAMAGE_AMOUT component as they are applied before the CO effects.
	float newBaseDamageOfWeapon = damageInstance->baseDamageValue + bonusDamage; 
#if DEBUG_CONDITION_OVERLOAD_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Old base damage of weapon = " + std::to_string(damageInstance->baseDamageValue));
	ServiceLocator::GetService<ILogService>()->Log("New base damage of weapon = " + std::to_string(newBaseDamageOfWeapon));
#endif

	*damageInstance *= newBaseDamageOfWeapon / damageInstance->baseDamageValue;

	// This process replicates the problem that CO mod effects do not take into account flat additive bonuses to base damage
	// This could be counteracted by getting the addToBaseBonus for normal WEAPON_DAMAGE_AMOUNT mods again
	// e.g.
	// std::map<ModOperationType, float> weaponDamageModEffectValues = ModProcessingFunctions::CalculateModEffects(damageInstance, ModUpgradeType::WEAPON_DAMAGE_AMOUNT);
	// baseDamageOfWeapon += weaponDamageModEffectValues[ModOperationType::ADD_TO_BASE_VALUE];

	// Apply any multiply bonuses (akin to the way projectile weapons work with this process)
	*damageInstance *= modEffectValues[ModOperationType::MULTIPLY];
}