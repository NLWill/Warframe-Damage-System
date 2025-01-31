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
	DamageInstance(Weapon &_weapon, std::string _attackName, Target &target, std::string targetBodyPart);
	std::vector<DamageValue> damageData;
	std::vector<StatusEffect> statusEffects;
	Weapon *weapon;
	std::string attackName;

	float moddedCriticalChance;
	float moddedCriticalDamage;
	int critTier;
	float moddedStatusChance;
	float moddedStatusDamageMultiplier;

	// Target Information
	Target *target; // Target class contains all data relevant to faction, hitzones etc.
	std::string targetBodyPart;

	std::vector<ModEffectBase *> GetAllModEffects(ModUpgradeType upgradeType);

	DamageInstance &operator*(const float &mult);
	DamageInstance &operator=(const DamageInstance &other);
	DamageInstance &operator*=(const float &mult);
	float GetTotalDamage();

	//Fulfil all contracts for the DamageInstanceModEffectInterface
	
	virtual std::vector<DamageValue> GetDamageData();
	virtual void AddDamageValue(DamageValue damageValue);
	virtual std::vector<StatusEffect> GetStatusEffects();
	virtual void AddStatusEffect(StatusEffect statusEffect);

	virtual std::string GetAttackName();

	virtual std::string GetWeaponCategory();
	virtual float GetFireRate();
	virtual float GetCriticalChance();
	virtual float GetCriticalDamage();
	virtual float GetCriticalTier();
	virtual float GetStatusChance();
	virtual float GetStatusDamageMultiplier();

	virtual int GetModSetCount(std::string setName);

	virtual int GetTargetLevel();
	virtual float GetTargetMaxHealth();
	virtual float GetTargetCurrentHealth();
	virtual Faction GetTargetFaction();
	virtual bool IsTargetHitzoneWeakPoint();
	virtual bool IsTargetHitzoneHeadshot();
	virtual float GetTargetHitzoneMultiplier();
	virtual float GetTargetArmour();
	virtual std::vector<StatusEffect> GetStatusEffectsOnTarget();
};