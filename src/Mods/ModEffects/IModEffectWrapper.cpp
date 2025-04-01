#include "src/Mods/ModEffects/IModEffectWrapper.h"

DamageType IModEffectWrapper::GetDamageType()
{
	return _wrappedModEffect->GetDamageType();
}

ModOperationType IModEffectWrapper::GetModOperationType()
{
	return _wrappedModEffect->GetModOperationType();
}

ModUpgradeType IModEffectWrapper::GetUpgradeType()
{
	return _wrappedModEffect->GetUpgradeType();
}
