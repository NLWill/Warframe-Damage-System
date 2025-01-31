#pragma once
#include "src/Mods/ModEffectBase.h"

struct FactionModEffect : public ModEffectBase{
	public:
	FactionModEffect(ModOperationType operationType, float value, Faction requiredFaction);
	virtual ~FactionModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(DamageInstanceModEffectInterface *damageInstance);

	private:
	ModOperationType _operationType; // What numerical operation does the mod perform on the affected stat
	ModUpgradeType _upgradeType; // What part of the process the mod is involved
	float _value;	// The magnitude of effect for this operation
	Faction _requiredFaction;
};