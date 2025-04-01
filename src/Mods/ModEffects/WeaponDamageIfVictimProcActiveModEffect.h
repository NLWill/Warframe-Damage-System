#pragma once
#include "src/Mods/ModEffects/ISinglePurposeModEffect.h"

struct WeaponDamageIfVictimProcActiveModEffect : public ISinglePurposeModEffect
{
public:
	WeaponDamageIfVictimProcActiveModEffect(ModOperationType operationType, float value);
	virtual ~WeaponDamageIfVictimProcActiveModEffect() = default;

	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance);
};