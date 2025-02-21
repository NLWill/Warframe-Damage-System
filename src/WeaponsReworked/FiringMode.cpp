#include "src/WeaponsReworked/FiringMode.h"

FiringMode::FiringMode(std::string firingModeName, std::vector<DamageData> attackBreakdown)
{
	this->firingModeName = firingModeName;
	this->attackBreakdown = attackBreakdown;

	// Set default values
	fireRate = 1;
	ammoShotRequirement = 1;
	reloadTime = 1;
}