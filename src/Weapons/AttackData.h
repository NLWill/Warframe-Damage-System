#pragma once
#include<string>
#include<map>
#include<vector>
#include "src/Weapons/DamageType.h"
#include "src/Weapons/StatusEffect.h"
#include "src/DamagePipeline/DamageValue.h"

struct AttackData{
public:
	// Constructor with only the necessary data
	AttackData() = default;
	AttackData(std::vector<DamageValue> inputAttackData, float criticalChance, float criticalDamage, float statusChance, float fireRate, std::string hitType);
	std::string attackName;
	float ammoRequirement;
	std::string ammoType;
	std::vector<DamageValue> attackData;
	float criticalChance;
	float criticalDamage;
	float statusChance;
	float fireRate;
	float multishot;
	std::string hitType;
	std::string fireMode;
	
	// For burst firing mode
	int numShots;
	float burstDelay;
	
	// For charge based attacks
	float chargeTime;
		
	// For explosives
	std::map<std::string, float> damageFallOff;
	float embedTime; // Delay for explosions after impact
	float damageRadius;
	
	// Special Effects
	std::vector<StatusEffect> forcedProcs;
	float effectDuration;	// Duration for special effects
	float headshotDamageBonus;
	bool isSilenced;
	float maxSpread;
	float minSpread;
	float punchThrough;
	float projectileSpeed;
};