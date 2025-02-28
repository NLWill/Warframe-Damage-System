#include "src/DamagePipeline/HitZoneProcess/HitZoneProcess.h"

void HitZoneProcess::ApplyHitZoneDamageMultiplier(DamageInstance *damageInstance)
{
	float hitZoneMultiplier = damageInstance->target->GetBodyPartMultiplier(damageInstance->targetBodyPart);

	hitZoneMultiplier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_HITZONE_MODIFIER, hitZoneMultiplier);
	
	*damageInstance *= hitZoneMultiplier;
}