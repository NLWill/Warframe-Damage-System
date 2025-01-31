#pragma once
#include "src/Mods/ModEffectBase.h"

struct ProbabilityModEffect : public ModEffectBase{
public:
	ProbabilityModEffect(ModEffectBase& wrapped, float probabilityOfSucess);
	virtual ~ProbabilityModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(DamageInstanceModEffectInterface *damageInstance);

private:
	ModEffectBase& _wrapped;
	float _probabilityOfSuccess;
};