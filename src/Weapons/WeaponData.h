#pragma once
#include<string>
#include<vector>
#include<map>
#include "src/Weapons/AttackData.h"
#include "src/Mods/ModPolarity.h"
#include "src/Mods/ModBase.h"
#include "src/Weapons/DamageType.h"
#include "src/Weapons/Incarnon/Incarnon.h"

struct WeaponData{
public:
// Constructor with only the necessary data
	WeaponData(std::string _name, std::map<std::string, AttackData> _attacks);
	WeaponData(const WeaponData &other);
	std::string name;
	int id;
	std::string fileName;
	std::map<std::string, AttackData> attacks;
	std::vector<Mod*> innateUpgrades;
	Incarnon incarnonUpgrades;
	
	// Ammo related details
	int ammoCapacity;
	int ammoPickupCount;
	int magazineSize;
	float reloadTime;
	std::string reloadStyle;
	
	// For battery based weapons
	float reloadDelay;
	float reloadDelayEmpty;
	float batteryRegenRate;
	
	// For Spooling Weapons
	int spoolShotRamp;
	
	// Misc
	std::string weaponCategory;
	std::string equipSlot;
	std::vector<std::string> compatabilityTags;
	std::string weaponFamily;
	bool isLichWeapon;
	DamageType lichWeaponElement;
	float lichWeaponElementBonus;
	int levelCap;
	int masteryReq;
	
	// Riven details
	float rivenDisposition;
	
	// Modding Details
	int normalModSlotCount, auraSlotCount, exilusSlotCount, arcaneSlotCount;
	std::vector<ModPolarity> modPolarities;	// Vector of mod polarities, including normal mods, aura mod, exilus mods, and arcanes. In that order.
	
	// For snipers
	int hitNextTierOperator;
	float comboResetDelay;
};