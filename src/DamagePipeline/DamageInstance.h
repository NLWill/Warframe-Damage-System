#pragma once
#include <map>
#include <vector>
#include <memory>
#include "src/Weapons/DamageType.h"
#include "src/Weapons/StatusEffect.h"
#include "src/DamagePipeline/DamageValue.h"
#include "src/Mods/IModEffect.h"
#include "src/Weapons/Weapon.h"
#include "src/Target/Target.h"
#include "src/DamagePipeline/IDamageInstance.h"
#include "src/DamagePipeline/FlaggedVariable.h"

class DamageInstance : public IDamageInstance, std::enable_shared_from_this<DamageInstance>
{
public:
	DamageInstance();
	DamageInstance(const DamageInstance &other);
	DamageInstance(std::shared_ptr<Weapon> _weapon, std::string attackName, DamageData damageData, std::shared_ptr<Target> target, std::string targetBodyPart, bool averageCalculation = false);
	~DamageInstance();

	std::shared_ptr<DamageInstance> GetPtr();

	bool calculateAverageDamage;

	std::shared_ptr<Weapon> weapon;
	std::string attackName;
	DamageData damageData;

	float baseDamageValue;
	std::map<DamageType, float> elementalWeights;
	std::vector<DamageValue> damageValues;
	std::vector<StatusEffect> statusEffects;
	void AddStatusEffect(StatusEffect statusEffect);

	FlaggedVariable<float> moddedCriticalChance;
	FlaggedVariable<float> moddedCriticalDamage;
	FlaggedVariable<float> critTier;
	FlaggedVariable<float> moddedStatusChance;
	FlaggedVariable<float> moddedStatusDamageMultiplier;
	FlaggedVariable<float> moddedStatusDurationMultiplier;

	// Target Information
	std::shared_ptr<Target> target; // Target class contains all data relevant to faction, hitzones etc.
	std::string targetBodyPart;

	/// @brief Get all the mod effects that are going to affect the provided ModUpgradeType
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @return A vector of all mod effects which have an effect on the targeted variable
	std::vector<std::shared_ptr<IModEffect>> GetAllModEffects(ModUpgradeType upgradeType);

	/// @brief Run through all sources of mod effects and apply all mod effects related to the provided ModUpgradeType
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @param modEffectValues The map of floats that stores the quantities of each ModOperationType over all mods
	/// @note This function is static rather than being a member function as shared_from_this would too often give bad_weak_ptr exception
	static void EvaluateModEffects(std::shared_ptr<DamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues);

	DamageInstance &operator*(const float &mult);
	DamageInstance &operator=(const DamageInstance &other);
	DamageInstance &operator*=(const float &mult);
	virtual float GetTotalDamage();

	//Fulfil all contracts for the IDamageInstance
	
	virtual std::vector<DamageValue> GetDamageValues();
	virtual bool IsAverageDamageCalculation();
	virtual void AddDamageValue(DamageValue damageValue);
	virtual std::map<DamageType, float> &GetElementalWeights();
	virtual std::vector<ProcType> GetTriggeredProcTypes();

	virtual std::string GetAttackName();
	virtual DamageData GetDamageData();

	virtual std::string GetWeaponCategory();
	virtual float GetFireRate();
	virtual float GetCriticalChance();
	virtual float GetCriticalDamage();
	virtual float GetCriticalTier();
	virtual float GetStatusChance();
	virtual float GetStatusDamageMultiplier();
	virtual float GetStatusDurationMultiplier();
	virtual int GetMagazineCapacity();
	virtual float GetAmmoEfficiency();

	virtual int GetModSetCount(std::string setName);

	virtual std::string GetTargetBodyPart();
	virtual int GetTargetLevel();
	virtual float GetTargetMaxHealth();
	virtual float GetTargetCurrentHealth();
	virtual Faction GetTargetFaction();
	virtual bool IsTargetHitzoneWeakPoint();
	virtual bool IsTargetHitzoneHeadshot();
	virtual float GetTargetHitzoneMultiplier();
	virtual float GetTargetArmour();
	virtual std::vector<ProcType> GetStatusEffectsOnTarget();

	private:
};