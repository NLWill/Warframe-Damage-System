#pragma once
#include <map>
#include <vector>
#include "src/Weapons/DamageType.h"
#include "src/Weapons/StatusEffect.h"
#include "src/DamagePipeline/DamageValue.h"

class DamageInstance
{
public:
	DamageInstance();
	DamageInstance(std::vector<DamageValue> baseDamageData);
	DamageInstance(const DamageInstance &other);
	std::vector<DamageValue> damageData;
	std::vector<StatusEffect> statusEffects;
	int critTier;

	DamageInstance(const std::vector<DamageValue> &_damageData);

	DamageInstance &operator*(const float &mult);
	DamageInstance &operator=(const DamageInstance &other);
	DamageInstance &operator*=(const float &mult);
	float GetTotalDamage();
	void AddDamageValue(DamageValue damageValue);
	void AddStatusEffect(StatusEffect statusEffect);
};