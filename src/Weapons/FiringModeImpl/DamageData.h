#pragma once
#include "src/Weapons/DamageType.h"
#include "src/Weapons/ProcType.h"
#include <map>
#include "src/Weapons/FiringModeImpl/AttackType.h"

struct DamageData
{
public:
	DamageData() = default;
	DamageData(std::map<DamageType, float> &percentageDamageDistribution,
			   float damageTotal,
			   HitType hitType,
			   float critChance,
			   float critDamage,
			   float statusChance,
			   float multishot);
	std::map<DamageType, float> percentageDamageDistribution;
	float damageTotal;
	HitType hitType;
	float critChance;
	float critDamage;
	float statusChance;
	float multishot;
	std::vector<ProcType> forcedProcs;
	bool disableHeadshotMultiplier;

private:
};
