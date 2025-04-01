#include "src/Mods/ModEffects/WeaponDamageIfVictimProcActiveModEffect.h"
#include "src/Weapons/StatusEffect.h"
#include <map>
#include <algorithm>

WeaponDamageIfVictimProcActiveModEffect::WeaponDamageIfVictimProcActiveModEffect(ModOperationType operationType, float value)
{
	_operationType = operationType;
	_value = value;

	_damageType = DamageType::DT_ANY;
	_upgradeType = ModUpgradeType::WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE;
}

float WeaponDamageIfVictimProcActiveModEffect::GetModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	// If not AoE, multiply the number of unique status effects on the target by _value
	// Count the number of unique status effects on the target
	int uniqueStatusEffectCount = 0;
	std::map<ProcType, int> uniqueStatuses;
	for (auto status : damageInstance->GetStatusEffectsOnTarget())
	{
		uniqueStatuses[status]++;
	}
	uniqueStatusEffectCount = uniqueStatuses.size();

	return uniqueStatusEffectCount * _value;
}

float WeaponDamageIfVictimProcActiveModEffect::GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	// If not AoE, multiply the number of unique status effects on the target by _value
	// Count the number of unique status effects on the target
	int uniqueStatusEffectCount = 0;
	std::map<ProcType, int> uniqueStatuses;
	for (auto status : damageInstance->GetStatusEffectsOnTarget())
	{
		uniqueStatuses[status]++;
	}
	uniqueStatusEffectCount = uniqueStatuses.size();

	return uniqueStatusEffectCount * _value;
}

/*
// This was an experiment to estimate the total uptime of statuses from the weapon. It failed to account for multiple sub-attacks from the weapon
float WeaponDamageIfVictimProcActiveModEffect::GetAverageModValue(std::shared_ptr<DamageInstanceModEffectInterface> damageInstance)
{
	// Iterate over all status effects that the weapon may apply and calculate the average uptime that each may have
	float statusChance = damageInstance->GetStatusChance();
	float fireRate = damageInstance->GetFireRate();
	float statusDurationModifier = damageInstance->GetStatusDurationMultiplier();

	// Calculate the probability of rolling a status per shot from the damage distribution
	std::map<ProcType, float> probabilityOfStatusPerShot;

	float totalDamage = damageInstance->GetTotalDamage();
	for (auto &damageValue : damageInstance->GetDamageValues())
	{
		probabilityOfStatusPerShot[ProcType::GetProcTypeFromElement(damageValue.damageType)] += statusChance * damageValue.value / totalDamage;
	}

	// Add guaranteed forced procs
	for (auto procType : damageInstance->GetDamageData().forcedProcs)
	{
		probabilityOfStatusPerShot[procType] += 1;
	}

	// Iterate over each status probability and calculate the average uptime that each will have with continuous firing, ignoring reloads
	float avgUniqueStatusesAtAnyOneTime = 0;
	for (auto procTypeProbabilityPair : probabilityOfStatusPerShot)
	{
		float statusDuration = StatusEffect::GetBaseStatusDuration(procTypeProbabilityPair.first) * statusDurationModifier;

		// This is a statistical hack but it is quick and approximately accurate
		float avgShotsPerApplication = 1 / procTypeProbabilityPair.second;
		float avgTimeBetweenProcs = avgShotsPerApplication / fireRate;
		float percentageUptime = statusDuration / avgTimeBetweenProcs;

		// Limit percentage uptime to realistic values, as multiple instances of the same proc do not count twice
		percentageUptime = std::clamp(percentageUptime, (float)0, (float)1);
		avgUniqueStatusesAtAnyOneTime += percentageUptime;
	}

	return avgUniqueStatusesAtAnyOneTime * _value;
}
*/
