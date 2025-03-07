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
	FireInstance(std::shared_ptr<Weapon> _weapon, std::string _attackName);
	~FireInstance();

	/// @brief Vector of DamageInstances which represent all possible bullets and sub-attacks created in this trigger pull
	std::vector<std::shared_ptr<DamageInstance>> damageInstances;

	/// @brief Shared pointer to the weapon which triggered the FireInstance
	std::shared_ptr<Weapon> weapon;
	/// @brief Name of the FiringMode on the weapon that triggered the FireInstance
	std::string attackName;

	/// @brief The modded multishot on the weapon which decides the number of damage instances created
	float moddedMultishot;
	
	/// @brief Get the sum of the total damage dealt for all damage instances in this FireInstance
	/// @return 
	float GetTotalDamage();

private:
};