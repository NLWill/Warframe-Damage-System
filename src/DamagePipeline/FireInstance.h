#pragma once
#include <vector>
#include <string>
#include <memory>
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Weapons/Weapon.h"
#include "src/Target/Target.h"

class FireInstance
{
public:
	FireInstance() = default;
	FireInstance(FireInstance &other);
	FireInstance(shared_ptr<Weapon> _weapon, std::string _attackName);
	~FireInstance();
	std::vector<shared_ptr<DamageInstance>> damageInstances;

	shared_ptr<Weapon> weapon;
	std::string attackName;

	float moddedMultishot;
	
	float GetTotalDamage();

private:
};