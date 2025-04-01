#pragma once
#include<vector>
#include <string>
#include "src/DamagePipeline/DamageValue.h"
#include "src/Weapons/ProcType.h"
#include "src/Target/Faction.h"
#include "src/Weapons/FiringModeImpl/DamageData.h"

class IDamageInstance{
	public:
	/// @brief Get the sum of all damage types in this damage instance
	/// @return 
	virtual float GetTotalDamage() = 0;
	/// @brief Check whether the damage pipeline is evaluating the average damage or just a single instance
	/// @return Returns true if it is performing an average calculation
	virtual bool IsAverageDamageCalculation() = 0;
	/// @brief Get the vector of damage types and their corresponding values
	/// @return 
	virtual std::vector<DamageValue> GetDamageValues() = 0;
	/// @brief Add a new damage type and value to the damage instance
	/// @param damageValue 
	virtual void AddDamageValue(DamageValue damageValue) = 0;
	/// @brief Get the proportion of the baseDamageValue that each element constitutes
	virtual std::map<DamageType, float> &GetElementalWeights() = 0;
	/// @brief Get a vector of the proc types triggered in this damage instance
	/// @return 
	virtual std::vector<ProcType> GetTriggeredProcTypes() = 0;

	/// @brief Get the firing mode name of this damage instance
	/// @return 
	virtual std::string GetAttackName() = 0;
	/// @brief Get the originating DamageData that triggered this damage instance
	/// @return 
	virtual DamageData GetDamageData() = 0;

	/// @brief Get the category of the fired weapon
	/// @return 
	virtual std::string GetWeaponCategory() = 0;
	/// @brief Get the number of shots fired per second by this weapon, taking into account mods
	/// @return 
	virtual float GetFireRate() = 0;
	/// @brief Get the modded critical chance of this damage instance
	virtual float GetCriticalChance() = 0;
	/// @brief Get the modded critical damage of this damage instance
	virtual float GetCriticalDamage() = 0;
	/// @brief Get the final critical tier of this damage instance
	virtual float GetCriticalTier() = 0;
	/// @brief Get the modded status chance of this damage instance
	virtual float GetStatusChance() = 0;
	/// @brief Get the modded status damage multiplier of this damage instance
	virtual float GetStatusDamageMultiplier() = 0;
	/// @brief Get the modded status duration multiplier of this damage instance
	virtual float GetStatusDurationMultiplier() = 0;
	/// @brief Get the number of bullets in the weapon's magazine, taking into account mods
	virtual int GetMagazineCapacity() = 0;
	/// @brief Get the efficiency factor which scales the number of shots consumed per trigger pull
	virtual float GetAmmoEfficiency() = 0;

	/// @brief Get the number of mods equipped which are within a certain mod collection
	virtual int GetModSetCount(std::string setName) = 0;

	/// @brief Get the body part damaged by this damage instance
	virtual std::string GetTargetBodyPart() = 0;
	/// @brief Get the level of the target being damaged
	virtual int GetTargetLevel() = 0;
	/// @brief Get the maximum health of the damaged target
	virtual float GetTargetMaxHealth() = 0;
	/// @brief Get the current health of the damaged target
	virtual float GetTargetCurrentHealth() = 0;
	/// @brief Get the faction of the damaged target
	virtual Faction GetTargetFaction() = 0;
	/// @brief Evaluate whether the body part hit is a weak point
	virtual bool IsTargetHitzoneWeakPoint() = 0;
	/// @brief Evaluate whether the body part his is the head
	virtual bool IsTargetHitzoneHeadshot() = 0;
	/// @brief Get the damage multiplier associated with the damaged hitzone
	virtual float GetTargetHitzoneMultiplier() = 0;
	/// @brief Get the armour value of the damaged target
	virtual float GetTargetArmour() = 0;
	/// @brief Get a vector of the status types afflicted on the target
	virtual std::vector<ProcType> GetStatusEffectsOnTarget() = 0;
};