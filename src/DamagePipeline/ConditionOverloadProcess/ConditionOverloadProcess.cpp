#include "src/DamagePipeline/ConditionOverloadProcess/ConditionOverloadProcess.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

#define DEBUG_CONDITION_OVERLOAD_PROCESS false
#if DEBUG_CONDITION_OVERLOAD_PROCESS
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#endif

void ConditionOverloadProcess::EvaluateAndApplyConditionOverloadDamage(std::shared_ptr<DamageInstance> damageInstance)
{
	float baseDamageOfWeapon = damageInstance->damageData.damageTotal;
	#if DEBUG_CONDITION_OVERLOAD_PROCESS
ServiceLocator::GetService<ILogService>()->Log("Got base damage of weapon: " + std::to_string(baseDamageOfWeapon));
#endif
	auto coModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE);
	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = ModProcessingFunctions::CalculateModEffects(damageInstance, coModEffects);
	#if DEBUG_CONDITION_OVERLOAD_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Stacking multiply bonus: " + std::to_string(stackingMultiplyBonus));
#endif

	// This process replicates the problem that CO mod effects do not take into account flat additive bonuses to base damage
	// This could be counteracted by getting the addToBaseBonus for normal WEAPON_DAMAGE_AMOUNT mods again
	// e.g.
	// auto weaponDamageModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_DAMAGE_AMOUNT);
	// auto [weaponDamageAddToBaseBonus, weaponDamageStackingMultiplyBonus, weaponDamageMultiplyBonus, weaponDamageFlatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, weaponDamageModEffects, averageDamageCalculation);
	// baseDamageOfWeapon += weaponDamageAddToBaseBonus;

	float bonusDamage = baseDamageOfWeapon * (stackingMultiplyBonus);
	#if DEBUG_CONDITION_OVERLOAD_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Bonus damage to add = " + std::to_string(bonusDamage));
#endif
	float newBaseDamageOfWeapon = damageInstance->baseDamageValue + bonusDamage; // baseDamageOfWeapon * (normal WEAPON_DAMAGE_AMOUT bonuses) + baseDamageOfWeapon * (WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE bonuses)
	#if DEBUG_CONDITION_OVERLOAD_PROCESS
	ServiceLocator::GetService<ILogService>()->Log("Old base damage of weapon = " + std::to_string(damageInstance->baseDamageValue));
	ServiceLocator::GetService<ILogService>()->Log("New base damage of weapon = " + std::to_string(newBaseDamageOfWeapon));
#endif

	*damageInstance *= newBaseDamageOfWeapon / damageInstance->baseDamageValue;
}