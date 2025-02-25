#include "src/Mods/ModEffects/ConditionalModEffectWrapper.h"
#include <iostream>

ConditionalModEffect::ConditionalModEffect(ModEffectBase &wrapped, Conditional condition) : _wrapped{wrapped}, _condition{condition}
{
}

ConditionalModEffect::~ConditionalModEffect()
{
}

DamageType ConditionalModEffect::GetDamageType()
{
	return _wrapped.GetDamageType();
}

ModOperationType ConditionalModEffect::GetModOperationType()
{
	return _wrapped.GetModOperationType();
}

ModUpgradeType ConditionalModEffect::GetUpgradeType()
{
	return _wrapped.GetUpgradeType();
}

float ConditionalModEffect::GetModValue(DamageInstanceModEffectInterface *damageInstance)
{
	if (ConditionalOverrideManager::Instance().GetOverride(_condition))
	{
		return _wrapped.GetModValue(damageInstance);
	}
	else
	{
		return 0;
	}
}

float ConditionalModEffect::GetAverageModValue(DamageInstanceModEffectInterface *damageInstance)
{
	if (ConditionalOverrideManager::Instance().GetOverride(_condition))
	{
		return _wrapped.GetAverageModValue(damageInstance);
	}
	else
	{
		return 0;
	}
}
