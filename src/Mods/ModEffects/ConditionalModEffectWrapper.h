#pragma once
#include "src/Mods/ModEffects/IModEffectWrapper.h"
#include "src/Mods/ModEffects/ConditionalOverrideManager.h"

struct ConditionalModEffect : public IModEffectWrapper
{
public:
	ConditionalModEffect(std::shared_ptr<IModEffect> wrapped, Conditional conditional);
	virtual ~ConditionalModEffect() = default;

	virtual void EvaluateModEffect(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues);
	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance);

private:
	Conditional _condition;
};