#include "src/Weapons/FiringModeImpl/DamageData.h"

DamageData::DamageData(std::map<DamageType, float> &percentageDamageDistribution, float damageTotal, HitType hitType, float critChance, float critDamage, float statusChance, float multishot) : percentageDamageDistribution{percentageDamageDistribution}
{
	this->damageTotal = damageTotal;
	this->hitType = hitType;
	this->critChance = critChance;
	this->critDamage = critDamage;
	this->statusChance = statusChance;
	this->multishot = multishot;
	disableHeadshotMultiplier = false;
}