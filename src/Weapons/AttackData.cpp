#include "src/Weapons/AttackData.h"

AttackData::AttackData(std::vector<DamageValue> inputAttackData, float inputCriticalChance, float inputCriticalDamage, float inputStatusChance, float inputFireRate, std::string inputHitType)
{
	attackData = inputAttackData;
	criticalChance = inputCriticalChance;
	criticalDamage = inputCriticalDamage;
	statusChance = inputStatusChance;
	fireRate = inputFireRate;
	hitType = inputHitType;

	attackName = "Normal Attack";
	ammoType = "Primary";
	ammoRequirement = 1;
	multishot = 1;
	fireMode = "Semi-Auto";
	
	// For burst firing mode
	numShots = 0;
	burstDelay = 0;
	
	// For charge based attacks
	chargeTime = 0;
		
	// For explosives
	damageFallOff = {};
	embedTime = 0; // Delay for explosions after impact
	damageRadius = 0;
	
	// Special Effects
	forcedProcs = {};
	effectDuration = 0;	// Duration for special effects
	headshotDamageBonus = 0;
	isSilenced = false;
	maxSpread = 0;
	minSpread = 0;
	punchThrough = 0;
	projectileSpeed = 0;
}