#pragma once
#include<vector>
#include <string>
#include "src/DamagePipeline/DamageValue.h"
#include "src/Weapons/ProcType.h"
#include "src/Target/Faction.h"
#include "src/Weapons/FiringModeImpl/DamageData.h"

class DamageInstanceModEffectInterface{
	public:
	virtual float GetTotalDamage() = 0;
	virtual std::vector<DamageValue> GetDamageValues() = 0;
	virtual void AddDamageValue(DamageValue damageValue) = 0;
	// Get the proportion of the baseDamageValue that each element constitutes
	virtual std::map<DamageType, float> &GetElementalWeights() = 0;
	virtual std::vector<ProcType> GetTriggeredProcTypes() = 0;

	virtual std::string GetAttackName() = 0;
	virtual DamageData GetDamageData() = 0;

	virtual std::string GetWeaponCategory() = 0;
	virtual float GetFireRate() = 0;
	virtual float GetCriticalChance() = 0;
	virtual float GetCriticalDamage() = 0;
	virtual float GetCriticalTier() = 0;
	virtual float GetStatusChance() = 0;
	virtual float GetStatusDamageMultiplier() = 0;
	virtual float GetStatusDurationMultiplier() = 0;
	virtual int GetMagazineCapacity() = 0;
	virtual float GetAmmoEfficiency() = 0;

	virtual int GetModSetCount(std::string setName) = 0;

	virtual std::string GetTargetBodyPart() = 0;
	virtual int GetTargetLevel() = 0;
	virtual float GetTargetMaxHealth() = 0;
	virtual float GetTargetCurrentHealth() = 0;
	virtual Faction GetTargetFaction() = 0;
	virtual bool IsTargetHitzoneWeakPoint() = 0;
	virtual bool IsTargetHitzoneHeadshot() = 0;
	virtual float GetTargetHitzoneMultiplier() = 0;
	virtual float GetTargetArmour() = 0;
	virtual std::vector<ProcType> GetStatusEffectsOnTarget() = 0;
};