#pragma once
#include "src/Mods/ModEffectBase.h"
#include "src/Mods/ModOperationType.h"
#include "src/Weapons/DamageType.h"
#include "src/Mods/ModUpgradeType.h"

struct ConstantModEffect : public ModEffectBase{
	public:
	ConstantModEffect(DamageType damageType, ModUpgradeType upgradeType, ModOperationType operationType, float value);
	virtual ~ConstantModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);
	virtual float GetAverageModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);

	private:
	DamageType _damageType; // Set to DT_ANY for any mods not relating to elements
	ModOperationType _operationType; // What numerical operation does the mod perform on the affected stat
	ModUpgradeType _upgradeType; // What part of the process the mod is involved
	float _value;	// The magnitude of effect for this operation
};