#pragma once
#include "src/Mods/ModEffects/IModEffectWrapper.h"

struct ProbabilityModEffect : public IModEffectWrapper
{
public:
	ProbabilityModEffect(std::shared_ptr<IModEffect> wrapped, float probabilityOfSucess);
	virtual ~ProbabilityModEffect() = default;

	virtual void EvaluateModEffect(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues);
	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance);

private:
	float _probabilityOfSuccess;
};