
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
#include "src/Services/Logging/ILogService.h"
#endif

std::pair<float, float> DamagePipeline::RunDamagePipeline(std::shared_ptr<DamageInstance> damageInstance)
{
	ApplyBonusesAtTriggerPull(damageInstance);

	ApplyOnHitBonuses(damageInstance);

	// This is where the damage pipeline leaves the weapon and transfers to the target receiving damage
	auto [directDamage, dotDamage] = DealDamageToTarget(damageInstance);

#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("----------");
#endif
	return {directDamage, dotDamage};
}

// Run through the damage pipeline to calculate the average damage output per shot of the weapon
std::pair<float, float> DamagePipeline::RunAverageDamagePipeline(std::shared_ptr<DamageInstance> damageInstance)
{
	ApplyBonusesAtTriggerPull(damageInstance);

	ApplyOnHitBonuses(damageInstance);

	// This is where the damage pipeline leaves the weapon and transfers to the target receiving damage
	auto [directDamage, dotDamage] = DealDamageToTarget(damageInstance);

#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("----------");
#endif
	return {directDamage, dotDamage};
}

void DamagePipeline::ApplyBonusesAtTriggerPull(std::shared_ptr<DamageInstance> damageInstance)
{
	//-> Base Damage Mods
	BaseDamageProcess::EvaluateAndApplyBaseDamageMods(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Base Damage Mods, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Elements and Quantisation
	NetworkQuantisation::AddElementsAndQuantise(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Elements and Quantisation, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Extra Damage Multipliers
	ExtraDamageMultipliers::EvaluateAndApplyExtraMultipliers(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Extra Multipliers, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif
}

void DamagePipeline::ApplyOnHitBonuses(std::shared_ptr<DamageInstance> damageInstance)
{
	//-> ConditionOverload effects
	ConditionOverloadProcess::EvaluateAndApplyConditionOverloadDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Condition Overload effects, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Critical Hits
	CriticalHitProcess::EvaluateCriticalHitProcess(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Critical Hits, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Hit Zone Multipliers
	HitZoneProcess::ApplyHitZoneDamageMultiplier(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Hitzone bonuses, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif
}

std::pair<float, float> DamagePipeline::DealDamageToTarget(std::shared_ptr<DamageInstance> damageInstance)
{
	// Headshot bonuses apply twice to status effects, so it must be in here
	HitZoneProcess::ApplyHeadshotDamageMultiplier(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Headshot bonuses, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Faction Damage Multipliers
	FactionDamageProcess::EvaluateAndApplyFactionDamage(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Faction Damage, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	// Status effects are applied here and run the whole DealDamageToTarget pipeline again
	StatusChanceProcess::EvaluateStatusChanceProcess(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Status Chance, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Health Resistances
	HealthResistanceProcess::EvaluateAndApplyHealthResistanceDamageReduction(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Health Resistances, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
#endif

	//-> Armour
	ArmourProcess::EvaluateAndApplyArmourDamageReduction(damageInstance);
#if DEBUG_DAMAGE_PIPELINE
	ServiceLocator::GetService<ILogService>()->Log("After Armour, total dmg = " + std::to_string(damageInstance->GetTotalDamage()));
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
			std::shared_ptr<Weapon> statusEffectWeapon = std::make_shared<Weapon>(statusEffectWeaponData, damageInstance->weapon->modManager);

			std::shared_ptr<DamageInstance> statusEffectDamageInstance = std::make_shared<DamageInstance>(statusEffectWeapon, statusEffectAttackName, statusEffectDamageData, damageInstance->target, statusEffect.targetBodyPart, damageInstance->calculateAverageDamage);

			dotDamage += DealDamageToTarget(statusEffectDamageInstance).first;

#if DEBUG_DAMAGE_PIPELINE
			ServiceLocator::GetService<ILogService>()->Log("Inflicted status effect " + statusEffect.procType.ToString() + " dealing " + std::to_string(statusEffectDamageInstance->GetTotalDamage()) + " damage per tick for " + std::to_string(statusEffect.GetNumberOfDamageTicks()) + " ticks");
#endif
		}
	}

	return {directDamage, dotDamage};
}
