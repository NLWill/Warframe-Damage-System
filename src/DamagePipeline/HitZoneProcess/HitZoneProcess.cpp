#include "src/DamagePipeline/HitZoneProcess/HitZoneProcess.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"

void HitZoneProcess::ApplyHitZoneDamageMultiplier(std::shared_ptr<DamageInstance> damageInstance)
{
	float hitZoneMultiplier = damageInstance->target->GetBodyPartMultiplier(damageInstance->targetBodyPart);

	hitZoneMultiplier = ModProcessingFunctions::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_WEAK_POINT_MODIFIER, hitZoneMultiplier);

	*damageInstance *= hitZoneMultiplier;
}

void HitZoneProcess::ApplyHeadshotDamageMultiplier(std::shared_ptr<DamageInstance> damageInstance)
{
	if (damageInstance->IsTargetHitzoneHeadshot())
	{
		float headshotMultiplier = ModProcessingFunctions::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, 1);

		*damageInstance *= headshotMultiplier;
	}
}