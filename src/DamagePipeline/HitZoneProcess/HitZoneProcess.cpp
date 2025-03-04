#include "src/DamagePipeline/HitZoneProcess/HitZoneProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"

void HitZoneProcess::ApplyHitZoneDamageMultiplier(shared_ptr<DamageInstance> damageInstance)
{
	float hitZoneMultiplier = damageInstance->target->GetBodyPartMultiplier(damageInstance->targetBodyPart);

	hitZoneMultiplier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_WEAK_POINT_MODIFIER, hitZoneMultiplier);

	*damageInstance *= hitZoneMultiplier;
}

void HitZoneProcess::ApplyHeadshotDamageMultiplier(shared_ptr<DamageInstance> damageInstance)
{
	if (damageInstance->IsTargetHitzoneHeadshot())
	{
		float headshotMultiplier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, 1);

		*damageInstance *= headshotMultiplier;
	}
}