#pragma once
#include <vector>
#include <string>
#include "src/Weapons/FiringModeImpl/AttackData.h"

class FiringMode
{
public:
	FiringMode() = default;
	FiringMode(std::string firingModeName, AttackData attackData);

	// The name of this firing mode
	std::string firingModeName;
	// A struct containing the components of attack data for this firing mode
	AttackData attackData;
	// Whether the firing mode fires separate damage instances for multishot or a unified single damage instance
	bool combineMultishotIntoSingleInstance;
	// Amount of ammo that is consumed per damage instance
	float ammoShotRequirement;
	// Fire rate per second of the weapon
	float fireRate;
	// Time to reload the weapon
	float reloadTime;

private:
};
