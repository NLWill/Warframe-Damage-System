#include "src/Mods/ModEffects/FactionModEffect.h"

FactionModEffect::FactionModEffect(ModOperationType operationType, float value, Faction requiredFaction)
{
	_operationType = operationType;
	_value = value;
	_requiredFaction = requiredFaction;
}

FactionModEffect::~FactionModEffect()
{
}

DamageType FactionModEffect::GetDamageType()
{
	return DamageType::DT_ANY;
}

ModOperationType FactionModEffect::GetModOperationType()
{
	return _operationType;
}

ModUpgradeType FactionModEffect::GetUpgradeType()
{
	return ModUpgradeType::WEAPON_FACTION_DAMAGE;
}

float FactionModEffect::GetModValue(DamageInstanceModEffectInterface *damageInstance)
{
	if (damageInstance->GetTargetFaction() == _requiredFaction || _requiredFaction == Faction::NONE){
		return _value;
	}
	else return 0;
}
