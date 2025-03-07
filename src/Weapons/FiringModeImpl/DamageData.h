#pragma once
#include "src/Weapons/DamageType.h"
#include "src/Weapons/ProcType.h"
#include <map>
#include "src/Weapons/FiringModeImpl/HitType.h"

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
	/// @brief A breakdown of the proportion of the total damage that is associated with each element
	std::map<DamageType, float> percentageDamageDistribution;
	/// @brief The base damage value of this attack
	float damageTotal;
	/// @brief The operation through which this attack damages the target. E.g. hitscan, radial etc.
	HitType hitType;
	/// @brief The base chance that the attack will be a critical hit
	float critChance;
	/// @brief The base critical multiplier of the attack
	float critDamage;
	/// @brief The base chance that the attack will trigger a status
	float statusChance;
	/// @brief The base number of damage instances that this attack will create
	float multishot;
	/// @brief A vector of the status effects that are guaranteed to be triggered from this attack
	std::vector<ProcType> forcedProcs;
	/// @brief Boolean to override the target headshot multiplier and set it to 1x
	bool disableHeadshotMultiplier;

private:
};
