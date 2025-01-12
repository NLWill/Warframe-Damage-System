#include "src/DamagePipeline/HitZoneProcess/HitZoneProcess.h"

void HitZoneProcess::ApplyHitZoneDamageMultiplier(FireInstance *fireInstance)
{
	float hitZoneMultiplier = fireInstance->target->GetBodyPartMultiplier(fireInstance->targetBodyPart);
	for (int i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		*(fireInstance->damageInstances[i]) *= hitZoneMultiplier;
	}
}