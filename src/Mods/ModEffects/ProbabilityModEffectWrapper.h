#pragma once
#include "src/Mods/ModEffectBase.h"

struct ProbabilityModEffect : public ModEffectBase{
public:
	ProbabilityModEffect(ModEffectBase& wrapped, float probabilityOfSucess);
	virtual ~ProbabilityModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);
	virtual float GetAverageModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);

private:
	ModEffectBase& _wrapped;
	float _probabilityOfSuccess;
};