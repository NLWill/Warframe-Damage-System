#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class HitZoneProcess
{
public:
	static void ApplyHitZoneDamageMultiplier(shared_ptr<DamageInstance> damageInstance);
	static void ApplyHeadshotDamageMultiplier(shared_ptr<DamageInstance> damageInstance);

private:
};