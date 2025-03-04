
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/DamagePipeline/FireInstance.h"

#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"
#include "src/DamagePipeline/NetworkQuantisationProcess/NetworkQuantisation.h"
#include "src/DamagePipeline/StatusChanceProcess/StatusChanceProcess.h"
#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/DamagePipeline/ExtraDamageMultipliers/ExtraDamageMultipliers.h"
#include "src/DamagePipeline/ConditionOverloadProcess/ConditionOverloadProcess.h"
#include "src/DamagePipeline/HitZoneProcess/HitZoneProcess.h"
#include "src/DamagePipeline/FactionDamageProcess/FactionDamageProcess.h"
#include "src/DamagePipeline/HealthResistanceProcess/HealthResistanceProcess.h"
#include "src/DamagePipeline/ArmourProcess/ArmourProcess.h"

#define DEBUG_DAMAGE_PIPELINE true
#if DEBUG_DAMAGE_PIPELINE
#include "src/Services/ServiceLocator.h"
#endif

float DamagePipeline::EvaluateAndApplyModEffects(shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, float baseValue)
{
	// Fetch all mods that affect the ModUpgradeType
	auto modEffects = damageInstance->GetAllModEffects(upgradeType);

	auto [addToBaseBonus, stackingMultiplyBonus, multiplyBonus, flatAdditiveBonus] = DamagePipeline::CalculateModEffects(damageInstance, modEffects);

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

std::tuple<float, float, float, float> DamagePipeline::CalculateModEffects(shared_ptr<DamageInstance> damageInstance, std::vector<shared_ptr<ModEffectBase>> modEffects)
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

std::pair<float, float> DamagePipeline::RunDamagePipeline(shared_ptr<DamageInstance> damageInstance)
{
	//-> Base Damage Mods
	BaseDamageProcess::EvaluateAndApplyBaseDamageMods(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Base Damage Mods, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Elements and Quantisation
	NetworkQuantisation::AddElementsAndQuantise(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Elements and Quantisation, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Extra Damage Multipliers
	ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Extra Multipliers, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> ConditionOverload effects
	ConditionOverloadProcess::EvaluateAndApplyConditionOverloadDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Condition Overload effects, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Critical Hits
	CriticalHitProcess::EvaluateCriticalHitProcess(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Critical Hits, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Hit Zone Multipliers
	HitZoneProcess::ApplyHitZoneDamageMultiplier(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Hitzone bonuses, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	// This is where the damage pipeline leaves the weapon and transfers to the target receiving damage
	auto [directDamage, dotDamage] = DealDamageToTarget(damageInstance);

#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("----------");
#endif
	return {directDamage, dotDamage};
}

// Run through the damage pipeline to calculate the average damage output per shot of the weapon
std::pair<float, float> DamagePipeline::RunAverageDamagePipeline(shared_ptr<DamageInstance> damageInstance)
{
	//-> Base Damage Mods
	BaseDamageProcess::EvaluateAndApplyBaseDamageMods(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Base Damage Mods, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Elements and Quantisation
	NetworkQuantisation::AddElementsAndQuantise(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Elements and Quantisation, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Extra Damage Multipliers
	ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Extra Multipliers, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> ConditionOverload effects
	ConditionOverloadProcess::EvaluateAndApplyConditionOverloadDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Condition Overload effects, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Critical Hits
	CriticalHitProcess::EvaluateCriticalHitProcess(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Critical Hits, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Hit Zone Multipliers
	HitZoneProcess::ApplyHitZoneDamageMultiplier(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Hitzone bonuses, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	// This is where the damage pipeline leaves the weapon and transfers to the target receiving damage
	auto [directDamage, dotDamage] = DealDamageToTarget(damageInstance);

#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("----------");
#endif
	return {directDamage, dotDamage};
}

std::pair<float, float> DamagePipeline::DealDamageToTarget(shared_ptr<DamageInstance> damageInstance)
{
	// Headshot bonuses apply twice to status effects, so it must be in here
	HitZoneProcess::ApplyHeadshotDamageMultiplier(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Headshot bonuses, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Faction Damage Multipliers
	FactionDamageProcess::EvaluateAndApplyFactionDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Faction Damage, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	// Status effects are applied here and run the whole DealDamageToTarget pipeline again
	//-> Status Chance
	StatusChanceProcess::EvaluateStatusChanceProcess(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Status Chance, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Health Resistances
	HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Health Resistances, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Armour
	ArmourProcess::EvaluateAndApplyArmourDamageReduction(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Armour, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	float directDamage = damageInstance->GetTotalDamage();
	float dotDamage = 0;

	// Make the status Effects run the DealDamageToTarget Pipeline
	for (auto statusEffect : damageInstance->statusEffects)
	{
		if (StatusEffect::IsDamagingStatusEffect(statusEffect.procType))
		{
			std::map<DamageType, float> statusEffectDamageTypeDistribution = {{statusEffect.damageType, 1}};
			DamageData statusEffectDamageData{statusEffectDamageTypeDistribution, statusEffect.damage, HitType::HITSCAN, 0, 0, 0, 1};
			AttackData statusEffectAttackData{statusEffectDamageData};
			std::string statusEffectAttackName = "Status Effect Attack";
			FiringMode statusEffectFiringMode{statusEffectAttackName, statusEffectAttackData};
			WeaponData statusEffectWeaponData{statusEffect.procType.ToString() + " status effect", {{statusEffectAttackName, statusEffectFiringMode}}};
			statusEffectWeaponData.defaultSlottedUpgrades = damageInstance->weapon->weaponData.defaultSlottedUpgrades;
			statusEffectWeaponData.incarnonUpgrades = Incarnon(damageInstance->weapon->weaponData.incarnonUpgrades);
			shared_ptr<Weapon> statusEffectWeapon = make_shared<Weapon>(statusEffectWeaponData, damageInstance->weapon->modManager);

			shared_ptr<DamageInstance> statusEffectDamageInstance = make_shared<DamageInstance>(statusEffectWeapon, statusEffectAttackName, statusEffectDamageData, damageInstance->target, statusEffect.targetBodyPart, damageInstance->calculateAverageDamage);

			dotDamage += DealDamageToTarget(statusEffectDamageInstance).first;

#if DEBUG_DAMAGE_PIPELINE
			ServiceLocator::GetLogger().Log("Inflicted status effect " + statusEffect.procType.ToString() + " dealing " + std::to_string(statusEffectDamageInstance->GetTotalDamage()) + " damage per tick for " + std::to_string(statusEffect.GetNumberOfDamageTicks()) + " ticks");
#endif
		}
	}

	return {directDamage, dotDamage};
}
