#include "src/Weapons/FiringMode.h"

FiringMode::FiringMode(std::string firingModeName, AttackData attackData)
{
	this->firingModeName = firingModeName;
	this->attackData = attackData;

	// Set default values
	fireRate = 1;
	ammoShotRequirement = 1;
	reloadTime = 1;
	combineMultishotIntoSingleInstance = false;
}