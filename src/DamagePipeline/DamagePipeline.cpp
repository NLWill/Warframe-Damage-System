#include "src/DamagePipeline/FireInstance.h"

#include "src/DamagePipeline/DamagePipeline.h"
#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/BaseDamageProcess/BaseDamageProcess.h"
#include "src/DamagePipeline/NetworkQuantisationProcess/NetworkQuantisation.h"
#include "src/DamagePipeline/StatusChanceProcess/StatusChanceProcess.h"
#include "src/DamagePipeline/CriticalHitProcess/CriticalHitProcess.h"
#include "src/DamagePipeline/ExtraDamageMultipliers/ExtraDamageMultipliers.h"
#include "src/DamagePipeline/HitZoneProcess/HitZoneProcess.h"
#include "src/DamagePipeline/FactionDamageProcess/FactionDamageProcess.h"
#include "src/DamagePipeline/HealthResistanceProcess/HealthResistanceProcess.h"
#include "src/DamagePipeline/ArmourProcess/ArmourProcess.h"

#include "src/Services/ServiceLocator.h"

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
		float modValue = modEffects[i]->GetModValue(damageInstance);
		switch (modEffects[i]->GetModOperationType())
		{
		case ModOperationType::ADD_TO_BASE_VALUE:
			add_to_base_bonus += modValue;
			break;
		case ModOperationType::STACKING_MULTIPLY:
			stacking_multiply_bonus += modValue;
			break;
		case ModOperationType::MULTIPLY:
			multiply_bonus *= modValue;
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

float DamagePipeline::RunDamagePipeline(Weapon &weapon, std::string attackName, Target &target, std::string targetBodyPart)
{
	FireInstance *fireInstance = new FireInstance(weapon, attackName);

	bool debugPipeline = false;

	//-> Multishot
	MultishotProcess::EvaluateMultishotMods(fireInstance);
	int rolledMultishot = MultishotProcess::RollForMultishot(fireInstance);
	for (int i = 0; i < rolledMultishot; i++)
	{
		fireInstance->damageInstances.push_back(new DamageInstance(weapon, attackName, target, targetBodyPart));
	}
	if (debugPipeline) ServiceLocator::GetLogger().Log("After Multishot, total dmg = " + std::to_string(fireInstance->GetTotalDamage()));

	// Calculate the total damage per bullet
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		//-> Base Damage Mods
		BaseDamageProcess::EvaluateAndApplyBaseDamageMods(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Base Damage Mods, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Elements and Quantisation
		NetworkQuantisation::AddElementsAndQuantise(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Elements and Quantisation, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Status Chance
		StatusChanceProcess::EvaluateStatusChanceMods(fireInstance->damageInstances[i]);
		StatusChanceProcess::EvaluateStatusDamageMods(fireInstance->damageInstances[i]);
		StatusChanceProcess::EvaluateStatusDurationMods(fireInstance->damageInstances[i]);
		StatusChanceProcess::RollForStatus(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Status Chance, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Critical Hits
		CriticalHitProcess::EvaluateCriticalChanceMods(fireInstance->damageInstances[i]);
		CriticalHitProcess::EvaluateCriticalDamageMods(fireInstance->damageInstances[i]);
		CriticalHitProcess::RollForCriticalHits(fireInstance->damageInstances[i]);
		CriticalHitProcess::EvaluateCriticalTierMods(fireInstance->damageInstances[i]);
		CriticalHitProcess::ApplyCriticalHitDamage(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Critical Hits, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Extra Damage Multipliers
		ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Extra Multipliers, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Hit Zone Multipliers
		HitZoneProcess::ApplyHitZoneDamageMultiplier(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Hit Zone, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Faction Damage Multipliers
		FactionDamageProcess::EvaluateAndApplyFactionDamage(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Faction Damage, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Faction Damage
		//-> (status effects applied here)
		//-> Health Resistances
		HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Health Resistances, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));

		//-> Armour
		ArmourProcess::EvaluateAndApplyArmourDamageReduction(fireInstance->damageInstances[i]);
		if (debugPipeline) ServiceLocator::GetLogger().Log("After Armour, total dmg = " + std::to_string(fireInstance->damageInstances[i]->GetTotalDamage()));
	}


	if (debugPipeline) ServiceLocator::GetLogger().Log("Final total damage, accounting for multishot = " + std::to_string(fireInstance->GetTotalDamage()));
	return fireInstance->GetTotalDamage();
}