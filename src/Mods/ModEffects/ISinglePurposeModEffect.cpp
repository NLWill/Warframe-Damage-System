#include "src/Mods/ModEffects/ISinglePurposeModEffect.h"

void ISinglePurposeModEffect::EvaluateModEffect(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues)
{
	if (GetUpgradeType() != upgradeType)
	{
		return;
	}

	float value = damageInstance->IsAverageDamageCalculation() ? GetAverageModValue(damageInstance) : GetModValue(damageInstance);

	auto operationType = GetModOperationType();
	switch (operationType)
	{
	case ModOperationType::ADD_TO_BASE_VALUE:
	case ModOperationType::STACKING_MULTIPLY:
	case ModOperationType::ADD:
		modEffectValues[operationType] += value;
		break;
	case ModOperationType::MULTIPLY:
		modEffectValues[operationType] *= value;
		break;
	case ModOperationType::SET:
		modEffectValues[operationType] = value;
		break;
	default:
		break;
	}
}

DamageType ISinglePurposeModEffect::GetDamageType()
{
	return _damageType;
}

ModOperationType ISinglePurposeModEffect::GetModOperationType()
{
	return _operationType;
}

ModUpgradeType ISinglePurposeModEffect::GetUpgradeType()
{
	return _upgradeType;
}
