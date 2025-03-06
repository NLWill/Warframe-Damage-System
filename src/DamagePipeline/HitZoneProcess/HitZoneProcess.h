#pragma once
#include "src/DamagePipeline/DamageInstance.h"

class HitZoneProcess
{
public:
	static void ApplyHitZoneDamageMultiplier(std::shared_ptr<DamageInstance> damageInstance);
	static void ApplyHeadshotDamageMultiplier(std::shared_ptr<DamageInstance> damageInstance);

private:
};