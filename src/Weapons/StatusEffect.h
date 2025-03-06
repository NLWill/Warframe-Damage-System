#pragma once
#include "src/Weapons/ProcType.h"
#include "src/DamagePipeline/IDamageInstance.h"

class StatusEffect{
	public:
	StatusEffect();
	StatusEffect(ProcType procType, shared_ptr<IDamageInstance> originatingDamageInstance, float baseDamage);

	ProcType procType;
	float damage;
	DamageType damageType;
	float remainingDuration;
	std::string targetBodyPart;

	static float GetStatusDuration(ProcType procType);
	int GetNumberOfDamageTicks();
	static bool IsDamagingStatusEffect(ProcType procType);

	private:
	static DamageType GetDamageTypeOfStatusEffect(ProcType procType);
	static float GetTimeBeforeFirstDamageTick(ProcType procType);
};