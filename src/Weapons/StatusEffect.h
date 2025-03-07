#pragma once
#include "src/Weapons/ProcType.h"
#include "src/DamagePipeline/IDamageInstance.h"

class StatusEffect{
	public:
	StatusEffect();
	StatusEffect(ProcType procType, std::shared_ptr<IDamageInstance> originatingDamageInstance, float baseDamage);

	// The type of status effect triggered
	ProcType procType;
	// The damage the status effect will deal, before health resistances
	float damage;
	// What damage type the status effect will deal
	DamageType damageType;
	// A countdown timer for how long the status effect will be active
	float remainingDuration;
	// The body part that the status effect will damage. Some damage the initially hit body part whilst other hit centre of mass
	std::string targetBodyPart;

	// Get the duration that a status effect will last with no mods
	static float GetBaseStatusDuration(ProcType procType);
	// Get the remaining number of damage ticks that this status effect will deal
	int GetNumberOfDamageTicks();
	// Check whether the provided proc type deals any damage
	static bool IsDamagingStatusEffect(ProcType procType);

	private:
	// Find the damage type that the associated proc type will deal to the target
	static DamageType GetDamageTypeOfStatusEffect(ProcType procType);
	// Get the time delay before the first damage tick. AoE statuses typically proc at t=0, whereas single-target statuses delay until t=1
	static float GetTimeBeforeFirstDamageTick(ProcType procType);
};