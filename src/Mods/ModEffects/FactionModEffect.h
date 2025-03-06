#pragma once
#include "src/Mods/IModEffect.h"

struct FactionModEffect : public IModEffect{
	public:
	FactionModEffect(ModOperationType operationType, float value, Faction requiredFaction);
	virtual ~FactionModEffect();
	virtual DamageType GetDamageType();
	virtual ModOperationType GetModOperationType();
	virtual ModUpgradeType GetUpgradeType();
	virtual float GetModValue(shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(shared_ptr<IDamageInstance> damageInstance);

	private:
	ModOperationType _operationType; // What numerical operation does the mod perform on the affected stat
	ModUpgradeType _upgradeType; // What part of the process the mod is involved
	float _value;	// The magnitude of effect for this operation
	Faction _requiredFaction;
};