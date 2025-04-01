#pragma once
#include "src/Mods/ModEffects/ISinglePurposeModEffect.h"

struct FactionModEffect : public ISinglePurposeModEffect
{
public:
	FactionModEffect(ModOperationType operationType, float value, Faction requiredFaction);
	virtual ~FactionModEffect() = default;
	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance);
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance);

private:
	Faction _requiredFaction;
};