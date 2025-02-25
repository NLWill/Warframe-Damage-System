#pragma once
#include <map>
#include <vector>
#include "src/Weapons/DamageType.h"
#include "src/Weapons/StatusEffect.h"
#include "src/DamagePipeline/DamageValue.h"
#include "src/Mods/ModEffectBase.h"
#include "src/Weapons/Weapon.h"
#include "src/Target/Target.h"
#include "src/DamagePipeline/DamageInstanceModEffectInterface.h"

class DamageInstance : public DamageInstanceModEffectInterface
{
public:
	DamageInstance();
	DamageInstance(const DamageInstance &other);
	DamageInstance(Weapon &_weapon, std::string attackName, DamageData damageData, Target &target, std::string targetBodyPart);
	~DamageInstance();
	Weapon *weapon;
	std::string attackName;
	DamageData damageData;

	float baseDamageValue;
	std::map<DamageType, float> elementalWeights;
	std::vector<DamageValue> damageValues;
	std::vector<ProcType> statusEffects;

	float moddedCriticalChance;
	float moddedCriticalDamage;
	float critTier;
	float moddedStatusChance;
	float moddedStatusDamageMultiplier;
	float moddedStatusDurationMultiplier;

	// Target Information
	Target *target; // Target class contains all data relevant to faction, hitzones etc.
	std::string targetBodyPart;

	std::vector<ModEffectBase *> GetAllModEffects(ModUpgradeType upgradeType);

	DamageInstance &operator*(const float &mult);
	DamageInstance &operator=(const DamageInstance &other);
	DamageInstance &operator*=(const float &mult);
	virtual float GetTotalDamage();

	//Fulfil all contracts for the DamageInstanceModEffectInterface
	
	virtual std::vector<DamageValue> GetDamageValues();
	virtual void AddDamageValue(DamageValue damageValue);
	virtual std::map<DamageType, float> &GetElementalWeights();
	virtual std::vector<ProcType> GetStatusEffects();
	virtual void AddStatusEffect(ProcType statusEffect);

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

	virtual int GetModSetCount(std::string setName);

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