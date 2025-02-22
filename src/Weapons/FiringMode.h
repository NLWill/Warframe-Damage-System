#pragma once
#include <vector>
#include <string>
#include "src/Weapons/FiringModeImpl/AttackData.h"

class FiringMode
{
public:
	FiringMode() = default;
	FiringMode(std::string firingModeName, AttackData attackData);

	std::string firingModeName;
	AttackData attackData;
	float ammoShotRequirement;
	float fireRate;
	float reloadTime;

private:
};
