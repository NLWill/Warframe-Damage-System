#include "src/Mods/ModEffects/ModEffect.h"

ModEffect::ModEffect(DamageType damageType, ModUpgradeType upgradeType, ModOperationType operationType, float value)
{
	_damageType = damageType;
	_upgradeType = upgradeType;
	_operationType = operationType;
	_value = value;
}

ModEffect::~ModEffect()
{

}

DamageType ModEffect::GetDamageType()
{
	return _damageType;
}

ModOperationType ModEffect::GetModOperationType()
{
	return _operationType;
}

ModUpgradeType ModEffect::GetUpgradeType()
{
	return _upgradeType;
}

float ModEffect::GetModValue(DamageInstanceModEffectInterface *damageInstance)
{
	return _value;
}
