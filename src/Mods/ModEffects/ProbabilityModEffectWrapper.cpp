#include "src/Mods/ModEffects/ProbabilityModEffectWrapper.h"

ProbabilityModEffect::ProbabilityModEffect(IModEffect& wrapped, float probabilityOfSucess) : _wrapped(wrapped)
{
	_wrapped = wrapped;
	_probabilityOfSuccess = probabilityOfSucess;
}

ProbabilityModEffect::~ProbabilityModEffect()
{
}

DamageType ProbabilityModEffect::GetDamageType()
{
	return _wrapped.GetDamageType();
}

ModOperationType ProbabilityModEffect::GetModOperationType()
{
	return _wrapped.GetModOperationType();
}

ModUpgradeType ProbabilityModEffect::GetUpgradeType()
{
	return _wrapped.GetUpgradeType();
}

float ProbabilityModEffect::GetModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	bool success = ServiceLocator::GetRNG().WeightedRandomBool(_probabilityOfSuccess);

	if (success){
		return _wrapped.GetModValue(damageInstance);
	}
	else {
		return 0.0f;
	}
}

float ProbabilityModEffect::GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	return _probabilityOfSuccess * _wrapped.GetAverageModValue(damageInstance);
}
