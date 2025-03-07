#include "src/DamagePipeline/FactionDamageProcess/FactionDamageProcess.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"
#include "src/Target/Faction.h"

void FactionDamageProcess::EvaluateAndApplyFactionDamage(std::shared_ptr<DamageInstance> damageInstance)
{
	float baseFactionDamageMultiplier = 1;
	float factionDamageMultiplier = ModProcessingFunctions::EvaluateAndApplyModEffects(damageInstance, ModUpgradeType::WEAPON_FACTION_DAMAGE, baseFactionDamageMultiplier);
	*damageInstance *= factionDamageMultiplier;
}