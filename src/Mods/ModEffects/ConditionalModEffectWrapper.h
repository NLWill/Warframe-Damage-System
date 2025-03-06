#pragma once
#include "src/Mods/IModEffect.h"
#include "src/Mods/ModEffects/ConditionalOverrideManager.h"

struct ConditionalModEffect : public IModEffect{
public:
	ConditionalModEffect(std::shared_ptr<IModEffect> wrapped, Conditional conditional);
	virtual ~ConditionalModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance);

private:
	std::shared_ptr<IModEffect> _wrapped;
	Conditional _condition;
};