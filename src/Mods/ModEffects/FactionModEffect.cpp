#include "src/Mods/ModEffects/FactionModEffect.h"

FactionModEffect::FactionModEffect(ModOperationType operationType, float value, Faction requiredFaction)
{
	_operationType = operationType;
	_value = value;
	_requiredFaction = requiredFaction;

	_upgradeType = ModUpgradeType::GAMEPLAY_FACTION_DAMAGE;
	_damageType = DamageType::DT_ANY;
}

float FactionModEffect::GetModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	if (damageInstance->GetTargetFaction() == _requiredFaction || _requiredFaction == Faction::NONE)
	{
		return _value;
	}
	else
	{
		return 0;
	}
}

float FactionModEffect::GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	return GetModValue(damageInstance);
}
