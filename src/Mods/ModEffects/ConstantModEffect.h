#pragma once
#include "src/Mods/ModEffects/ISinglePurposeModEffect.h"
#include "src/Mods/ModOperationType.h"
#include "src/Weapons/DamageType.h"
#include "src/Mods/ModUpgradeType.h"

struct ConstantModEffect : public ISinglePurposeModEffect
{
public:
	ConstantModEffect(DamageType damageType, ModUpgradeType upgradeType, ModOperationType operationType, float value);
	virtual ~ConstantModEffect() = default;

	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance);
};