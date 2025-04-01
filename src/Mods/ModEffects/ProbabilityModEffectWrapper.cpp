#include "src/Mods/ModEffects/ProbabilityModEffectWrapper.h"
#include "src/Services/ServiceLocator.h"
#include "src/Services/RNG/IRNGService.h"

ProbabilityModEffect::ProbabilityModEffect(std::shared_ptr<IModEffect> wrapped, float probabilityOfSucess)
{
	_wrappedModEffect = wrapped;
	_probabilityOfSuccess = probabilityOfSucess;
}

void ProbabilityModEffect::EvaluateModEffect(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues)
{
	// This method works for the normal calculations but it does not for the average method
	// However further redesigning would be needed to allow this wrapper which is very rare in the game
	bool success = ServiceLocator::GetService<IRNGService>()->WeightedRandomBool(_probabilityOfSuccess);

	if (success)
	{
		_wrappedModEffect->EvaluateModEffect(damageInstance, upgradeType, modEffectValues);
	}
	else
	{
		// Fail the probability of success so do nothing
		return;
	}
}

float ProbabilityModEffect::GetModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	bool success = ServiceLocator::GetService<IRNGService>()->WeightedRandomBool(_probabilityOfSuccess);

	if (success){
		return _wrappedModEffect->GetModValue(damageInstance);
	}
	else {
		return 0.0f;
	}
}

float ProbabilityModEffect::GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	return _probabilityOfSuccess * _wrappedModEffect->GetAverageModValue(damageInstance);
}
