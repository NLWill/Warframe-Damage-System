#pragma once
#include<string>
#include<map>
#include<vector>
#include "src/Weapons/DamageType.h"
#include "src/Weapons/StatusEffect.h"
#include "src/DamagePipeline/DamageValue.h"

struct AttackData{
public:
	std::string attackName;
	int ammoRequirement;
	std::string ammoType;
	std::vector<DamageValue> attackData;
	float criticalChance;
	float criticalMultiplier;
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
	bool IsSilenced;
	float maxSpread;
	float minSpread;
	float punchThrough;
	float projectileSpeed;
};