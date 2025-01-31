#pragma once
#include <vector>
#include <string>
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Weapons/Weapon.h"
#include "src/Target/Target.h"

class FireInstance
{
public:
	FireInstance() = default;
	FireInstance(FireInstance &other);
	FireInstance(Weapon &_weapon, std::string _attackName);
	std::vector<DamageInstance *> damageInstances;

	Weapon *weapon;
	std::string attackName;

	float moddedMultishot;
	
	float GetTotalDamage();

private:
};