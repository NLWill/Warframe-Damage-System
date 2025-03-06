#pragma once
#include "src/Mods/IModEffect.h"

struct ProbabilityModEffect : public IModEffect{
public:
	ProbabilityModEffect(IModEffect& wrapped, float probabilityOfSucess);
	virtual ~ProbabilityModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(shared_ptr<IDamageInstance> damageInstance);

private:
	IModEffect& _wrapped;
	float _probabilityOfSuccess;
};