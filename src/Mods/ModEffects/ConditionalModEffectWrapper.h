#pragma once
#include "src/Mods/ModEffectBase.h"
#include "src/Mods/ModEffects/ConditionalOverrideManager.h"

struct ConditionalModEffect : public ModEffectBase{
public:
	ConditionalModEffect(shared_ptr<ModEffectBase> wrapped, Conditional conditional);
	virtual ~ConditionalModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);
	virtual float GetAverageModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);

private:
	shared_ptr<ModEffectBase> _wrapped;
	Conditional _condition;
};