#pragma once
#include "src/Weapons/ProcType.h"

class StatusEffect{
	public:
	StatusEffect();
	StatusEffect(ProcType procType, float damage);

	ProcType procType;
	float damage;
	float remainingDuration;

	static float GetStatusDuration(ProcType procType);
};