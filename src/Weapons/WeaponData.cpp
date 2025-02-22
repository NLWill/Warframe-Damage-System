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

	normalModSlotCount = 8;
	auraSlotCount = 0;
	exilusSlotCount = 1;
	arcaneSlotCount = 1;
	modPolarities = {};
	for (int i = 0; i < normalModSlotCount + auraSlotCount + exilusSlotCount + arcaneSlotCount; i++)
	{
		modPolarities.push_back(ModPolarity::AP_UNIVERSAL);
	}

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

	normalModSlotCount = 8;
	auraSlotCount = 0;
	exilusSlotCount = 1;
	arcaneSlotCount = 1;
	modPolarities = {};
	for (int i = 0; i < normalModSlotCount + auraSlotCount + exilusSlotCount + arcaneSlotCount; i++)
	{
		modPolarities.push_back(ModPolarity::AP_UNIVERSAL);
	}

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