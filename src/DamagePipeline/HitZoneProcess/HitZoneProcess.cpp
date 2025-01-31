#include "src/DamagePipeline/HitZoneProcess/HitZoneProcess.h"

void HitZoneProcess::ApplyHitZoneDamageMultiplier(DamageInstance *damageInstance)
{
	float hitZoneMultiplier = damageInstance->target->GetBodyPartMultiplier(damageInstance->targetBodyPart);
	*damageInstance *= hitZoneMultiplier;
}