#pragma once
#include <vector>
#include <string>
#include "src/Weapons/FiringModeImpl/DamageData.h"

class FiringMode
{
public:
	FiringMode(std::string firingModeName, std::vector<DamageData> attackBreakdown);
	
	std::string firingModeName;
	std::vector<DamageData> attackBreakdown;
	float ammoShotRequirement;
	float fireRate;
	float reloadTime;

private:
};
