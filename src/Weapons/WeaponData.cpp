#include "src/Weapons/WeaponData.h"
#include "WeaponData.h"

WeaponData::WeaponData()
{
	id = 0;
	name  = "";
	
	parent = "";
	parents = {};
	path = "";

	firingModes = {};
	ammoCapacity = INT32_MAX;
	ammoClipSize = 1;

	compatabilityTags ={};
	defaultSlottedUpgrades = {};
	incarnonUpgrades = Incarnon();

	equipTime = 0.5;
	inventorySlot = "";
	isKuva = false;
	levelCap = 30;
	omegaAttenuation = 0.5;
	productCategory = "";

}
WeaponData::WeaponData(std::string name, std::map<std::string, FiringMode> firingModes)
{
	id = 0;
	this->name = name;
	
	parent = "";
	parents = {};
	path = "";

	this->firingModes = firingModes;
	ammoCapacity = INT32_MAX;
	ammoClipSize = 1;


	compatabilityTags ={};
	defaultSlottedUpgrades = {};
	incarnonUpgrades = Incarnon();

	equipTime = 0.5;
	inventorySlot = "";
	isKuva = false;
	levelCap = 30;
	omegaAttenuation = 0.5;
	productCategory = "";
}

bool WeaponData::IsValidFiringMode(std::string name)
{
	if (firingModes.count(name) == 0)
	{
		std::string errorMsg = "Incorrect attack name provided. Available firing modes are: ";
		for (const auto &keyValuePair : firingModes)
		{
			errorMsg += "[";
			errorMsg += keyValuePair.first;
			errorMsg += "] ";
		}
		ServiceLocator::GetLogger().LogWarning(errorMsg);
		return false;
	}
	return true;
}
