#include "src/Mods/ModEffects/ConditionalModEffectWrapper.h"

ConditionalModEffect::ConditionalModEffect(std::shared_ptr<IModEffect> wrapped, Conditional condition) : _condition{condition}
{
	_wrappedModEffect = wrapped;
}

void ConditionalModEffect::EvaluateModEffect(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues)
{
	// Check that the required condition is fulfiled
	if (!ConditionalOverrideManager::Instance().GetOverride(_condition))
	{
		return;
	}

	_wrappedModEffect->EvaluateModEffect(damageInstance, upgradeType, modEffectValues);
}

float ConditionalModEffect::GetModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	if (ConditionalOverrideManager::Instance().GetOverride(_condition))
	{
		return _wrappedModEffect->GetModValue(damageInstance);
	}
	else
	{
		return 0;
	}
}

float ConditionalModEffect::GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance)
{
	if (ConditionalOverrideManager::Instance().GetOverride(_condition))
	{
		return _wrappedModEffect->GetAverageModValue(damageInstance);
	}
	else
	{
		return 0;
	}
}
