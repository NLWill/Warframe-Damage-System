#include "src/Weapons/WeaponData.h"
#include "WeaponData.h"

WeaponData::WeaponData(std::string _name, std::map<std::string, AttackData> _attacks)
{
	name = _name;
	fileName = "";
	attacks = _attacks;
	innateUpgrades = {};
	
	// Ammo related details
	ammoCapacity = 0;
	ammoPickupCount = 0;
	magazineSize = 0;
	reloadTime = 0;
	reloadStyle = "";
	
	// For battery based weapons
	reloadDelay = 0;
	reloadDelayEmpty = 0;
	batteryRegenRate = 0;
	
	// For Spooling Weapons
	spoolShotRamp = 0;
	
	// Misc
	weaponCategory = "Primary";
	equipSlot = "Primary";
	compatabilityTags = {};
	weaponFamily = {};
	isLichWeapon = false;
	lichWeaponElement = DamageType::DT_ANY;
	lichWeaponElementBonus = 0;
	levelCap = 30;
	masteryReq = 0;
	
	// Riven details
	rivenDisposition = 0.5;
	
	// Modding Details
	modSlotCount = 8;
	exilusPolarity = ModPolarity::POL_NONE;
	modPolarities = {};
	for (int i = 0; i < modSlotCount; i++)
	{
		modPolarities.push_back(ModPolarity::POL_NONE);
	}	
	
	// For snipers
	hitNextTierOperator = 0;
	comboResetDelay = 0;
}

WeaponData::WeaponData(const WeaponData &other)
{
	name = other.name;
	fileName = other.fileName;
	attacks = other.attacks;
	innateUpgrades = other.innateUpgrades;
	
	// Ammo related details
	ammoCapacity = other.ammoCapacity;
	ammoPickupCount = other.ammoPickupCount;
	magazineSize = other.magazineSize;
	reloadTime = other.reloadTime;
	reloadStyle = other.reloadStyle;
	
	// For battery based weapons
	reloadDelay = other.reloadDelay;
	reloadDelayEmpty = other.reloadDelayEmpty;
	batteryRegenRate = other.batteryRegenRate;
	
	// For Spooling Weapons
	spoolShotRamp = other.spoolShotRamp;
	
	// Misc
	weaponCategory = other.weaponCategory;
	equipSlot = other.equipSlot;
	compatabilityTags = other.compatabilityTags;
	weaponFamily = other.weaponFamily;
	isLichWeapon = other.isLichWeapon;
	lichWeaponElement = other.lichWeaponElement;
	lichWeaponElementBonus = other.lichWeaponElementBonus;
	levelCap = other.levelCap;
	masteryReq = other.masteryReq;
	
	// Riven details
	rivenDisposition = other.rivenDisposition;
	
	// Modding Details
	modSlotCount = other.modSlotCount;
	exilusPolarity = other.exilusPolarity;
	modPolarities = other.modPolarities;
	
	// For snipers
	hitNextTierOperator = other.hitNextTierOperator;
	comboResetDelay = other.comboResetDelay;
}