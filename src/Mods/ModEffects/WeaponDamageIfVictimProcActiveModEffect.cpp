#include "src/Mods/ModEffects/WeaponDamageIfVictimProcActiveModEffect.h"
#include "src/Weapons/StatusEffect.h"
#include <map>

WeaponDamageIfVictimProcActiveModEffect::WeaponDamageIfVictimProcActiveModEffect(ModOperationType operationType, float value)
{
	_operationType = operationType;
	_value = value;
}

WeaponDamageIfVictimProcActiveModEffect::~WeaponDamageIfVictimProcActiveModEffect()
{
}

DamageType WeaponDamageIfVictimProcActiveModEffect::GetDamageType()
{
	return DamageType::DT_ANY;
}

ModOperationType WeaponDamageIfVictimProcActiveModEffect::GetModOperationType()
{
	return _operationType;
}

ModUpgradeType WeaponDamageIfVictimProcActiveModEffect::GetUpgradeType()
{
	return ModUpgradeType::WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE;
}

float WeaponDamageIfVictimProcActiveModEffect::GetModValue(DamageInstanceModEffectInterface *damageInstance)
{
	// If not AoE, multiply the number of unique status effects on the target by _value
	// Count the number of unique status effects on the target
	int uniqueStatusEffectCount = 0;
	std::map<ProcType, int> uniqueStatuses;
	for (auto status : damageInstance->GetStatusEffectsOnTarget())
	{
		uniqueStatuses.at(status)++;
	}
	uniqueStatusEffectCount = uniqueStatuses.size();

	return uniqueStatusEffectCount * _value;
}
