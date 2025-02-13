#pragma once
#include "src/Mods/ModOperationType.h"
#include "src/Weapons/DamageType.h"
#include "src/Mods/ModUpgradeType.h"
#include "src/DamagePipeline/DamageInstanceModEffectInterface.h"

struct ModEffectBase{
	public:
	virtual ~ModEffectBase() {};
	virtual DamageType GetDamageType() = 0;
	virtual ModOperationType GetModOperationType() = 0;
	virtual ModUpgradeType GetUpgradeType() = 0;
	virtual float GetModValue(DamageInstanceModEffectInterface *damageInstance) = 0;
	virtual float GetAverageModValue(DamageInstanceModEffectInterface *damageInstance) = 0;
};