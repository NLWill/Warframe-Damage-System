#pragma once
#include "src/Mods/ModEffectBase.h"

struct WeaponDamageIfVictimProcActiveModEffect : public ModEffectBase{
	public:
public:
	WeaponDamageIfVictimProcActiveModEffect(ModOperationType operationType, float value);
	virtual ~WeaponDamageIfVictimProcActiveModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);
	virtual float GetAverageModValue(shared_ptr<DamageInstanceModEffectInterface> damageInstance);

	private:
	ModOperationType _operationType; // What numerical operation does the mod perform on the affected stat
	ModUpgradeType _upgradeType; // What part of the process the mod is involved
	float _value;	// The magnitude of effect for this operation
};