#pragma once
#include<vector>
#include<string>
#include "src/DamagePipeline/DamageInstance.h"
#include "include/Weapons/Weapon.h"

class FireInstance{
	public:
	std::vector<DamageInstance*> damageInstances;
	Weapon* Weapon;
	std::string attackName;

	float moddedCriticalChance;
	float moddedCriticalMultiplier;
	float moddedStatusChance;
	float moddedMultishot;
	
	// Target Information
	//Target* target;	Target class contains all data relevant to faction, hitzones etc.

	private:

};