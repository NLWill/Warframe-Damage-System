#include "src/DamagePipeline/FactionDamageProcess/FactionDamageProcess.h"
#include "src/Target/Faction.h"
#include "src/DamagePipeline/DamagePipeline.h"

void FactionDamageProcess::EvaluateAndApplyFactionDamage(std::shared_ptr<DamageInstance> damageInstance)
{
	float baseFactionDamageMultiplier = 1;
	float factionDamageMultiplier = DamagePipeline::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_FACTION_DAMAGE, baseFactionDamageMultiplier);
	*damageInstance *= factionDamageMultiplier;
}