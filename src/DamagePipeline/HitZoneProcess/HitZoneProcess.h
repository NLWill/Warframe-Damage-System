#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class HitZoneProcess
{
public:
	static void ApplyHitZoneDamageMultiplier(DamageInstance *damageInstance);
	static void ApplyHeadshotDamageMultiplier(DamageInstance *damageInstance);

private:
};