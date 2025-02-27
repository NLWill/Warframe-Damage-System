
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

#define DEBUG_DAMAGE_PIPELINE false
#if DEBUG_DAMAGE_PIPELINE
#include "src/Services/ServiceLocator.h"
#endif

float DamagePipeline::EvaluateAndApplyModEffects(DamageInstance *damageInstance, ModUpgradeType upgradeType, float baseValue)
{
	// Fetch all mods that affect the ModUpgradeType
	std::vector<ModEffectBase *> modEffects = damageInstance->GetAllModEffects(upgradeType);

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
	for (int i = 0; i < modEffects.size(); i++)
	{
		if (modEffects[i]->GetModOperationType() == ModOperationType::SET)
		{
			baseValue = modEffects[i]->GetModValue(damageInstance);
		}
	}

	return baseValue;
}

std::tuple<float, float, float, float> DamagePipeline::CalculateModEffects(DamageInstance *damageInstance, std::vector<ModEffectBase *> modEffects)
{
	float add_to_base_bonus = 0;
	float stacking_multiply_bonus = 0;
	float multiply_bonus = 1;
	float flat_additive_bonus = 0;

	for (int i = 0; i < modEffects.size(); i++)
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

float DamagePipeline::RunDamagePipeline(DamageInstance *damageInstance)
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

	//-> Status Chance
	StatusChanceProcess::EvaluateStatusChanceMods(damageInstance);
	StatusChanceProcess::EvaluateStatusDamageMods(damageInstance);
	StatusChanceProcess::EvaluateStatusDurationMods(damageInstance);
	StatusChanceProcess::RollForStatus(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Status Chance, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Extra Damage Multipliers
	ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Extra Multipliers, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> ConditionOverload effects
	ConditionOverloadProcess::EvaluateAndApplyConditionOverloadDamage(damageInstance);

	//-> Critical Hits
	CriticalHitProcess::ApplyCriticalHitDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Critical Hits, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	// This is where the damage pipeline leaves the weapon and transfers to the target receiving damage
	DealDamageToTarget(damageInstance);

	return damageInstance->GetTotalDamage();
}

// Run through the damage pipeline to calculate the average damage output per shot of the weapon
float DamagePipeline::RunAverageDamagePipeline(DamageInstance *damageInstance)
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

	//-> Status Chance
	StatusChanceProcess::EvaluateStatusChanceMods(damageInstance);
	StatusChanceProcess::EvaluateStatusDamageMods(damageInstance);
	StatusChanceProcess::EvaluateStatusDurationMods(damageInstance);
	StatusChanceProcess::RollForStatus(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Status Chance, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Critical Hits
	CriticalHitProcess::ApplyCriticalHitDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Critical Hits, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Extra Damage Multipliers
	ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Extra Multipliers, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> ConditionOverload effects
	ConditionOverloadProcess::EvaluateAndApplyConditionOverloadDamage(damageInstance);

	// This is where the damage pipeline leaves the weapon and transfers to the target receiving damage
	DealDamageToTarget(damageInstance);

	return damageInstance->GetTotalDamage();
}

float DamagePipeline::DealDamageToTarget(DamageInstance *damageInstance)
{
	//-> Hit Zone Multipliers
	HitZoneProcess::ApplyHitZoneDamageMultiplier(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Hit Zone, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Faction Damage Multipliers
	FactionDamageProcess::EvaluateAndApplyFactionDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Faction Damage, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Faction Damage
	//-> (status effects applied here)
	//-> Health Resistances
	HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Health Resistances, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Armour
	ArmourProcess::EvaluateAndApplyArmourDamageReduction(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetLogger().Log("After Armour, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
	ServiceLocator::GetLogger().Log("----------");
#endif

	return damageInstance->GetTotalDamage();
}
