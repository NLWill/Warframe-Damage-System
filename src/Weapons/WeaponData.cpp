#include "src/Weapons/WeaponData.h"

WeaponData::WeaponData(std::string name, std::map<std::string, AttackData> attacks)
{
	this->name = name;
	std::string fileName = "";
	this->attacks = attacks;
	std::vector<Mod*> innateUpgrades = {};
	
	// Ammo related details
	int ammoCapacity = 0;
	int ammoPickupCount = 0;
	int magazineSize = 0;
	float reloadTime = 0;
	std::string reloadStyle = "";
	
	// For battery based weapons
	float reloadDelay = 0;
	float reloadDelayEmpty = 0;
	float batteryRegenRate = 0;
	
	// For Spooling Weapons
	int spoolShotRamp = 0;
	
	// Misc
	std::string weaponCategory = "Primary";
	std::string equipSlot = "Primary";
	std::vector<std::string> compatabilityTags = {};
	std::string weaponFamily = {};
	bool isLichWeapon = false;
	DamageType lichWeaponElement = DamageType::DT_ANY;
	float lichWeaponElementBonus = 0;
	int levelCap = 30;
	int masteryReq = 0;
	
	// Riven details
	float rivenDisposition = 0.5;
	
	// Modding Details
	int modSlotCount = 8;
	ModPolarity exilusPolarity = ModPolarity::None;
	std::vector<ModPolarity> modPolarities = {};
	for (int i = 0; i < modSlotCount; i++)
	{
		modPolarities.push_back(ModPolarity::None);
	}	
	
	// For snipers
	int hitNextTierOperator = 0;
	float comboResetDelay = 0;
}