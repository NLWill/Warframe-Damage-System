#pragma once
#include "src/Mods/ModEffectBase.h"
#include "src/Mods/ModEffects/ConditionalOverrideManager.h"

struct ConditionalModEffect : public ModEffectBase{
public:
	ConditionalModEffect(ModEffectBase& wrapped, Conditional conditional);
	virtual ~ConditionalModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(DamageInstanceModEffectInterface *damageInstance);
	virtual float GetAverageModValue(DamageInstanceModEffectInterface *damageInstance);

private:
	ModEffectBase& _wrapped;
	Conditional _condition;
};