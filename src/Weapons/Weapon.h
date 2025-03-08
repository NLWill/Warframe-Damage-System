#pragma once
#include <memory>
#include "src/Weapons/WeaponData.h"
#include <string>
#include <vector>
#include "src/Mods/IModManager.h"
#include "src/Target/Target.h"
#include "src/Weapons/IWeapon.h"

class Weapon : public std::enable_shared_from_this<Weapon>
{
public:
	Weapon(WeaponData &weaponData, std::shared_ptr<IModManager> modManager);
	~Weapon() = default;

	/// @brief Get the shared pointer instance surrounding the Weapon class.
	/// Requires this to be the case otherwise gets bad_weak_ptr exception.
	/// @return
	std::shared_ptr<Weapon> GetPtr();

	// Struct containing data innate to the weapon and it's firing modes.
	WeaponData weaponData;
	virtual WeaponData &GetWeaponData();

	// Struct handling equipping/removing mods and parsing values when needed.
	std::shared_ptr<IModManager> modManager;

	/// @brief Get a vector of ModEffects which affect the provided ModUpgradeType
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @return A vector of shared pointers to all mod effects which affect the associated ModUpgradeType
	std::vector<std::shared_ptr<IModEffect>> GetAllWeaponModEffects(ModUpgradeType upgradeType);

	/// @brief Get the modded fire rate of the weapon
	/// @param attackName The firing mode being queried
	/// @return Returns the number of shots per second output by the weapon
	float GetFireRate(std::string attackName);
	/// @brief Get the time to fully charge the weapon, taking into accout mods. For most non-charge-based weapons, this value will be 0.
	/// @param attackName The firing mode being queried
	/// @return
	float GetChargeTime(std::string attackName);
	/// @brief Get the modded magazine capacity of the weapon
	/// @return
	int GetMagazineCapacity();
	/// @brief Get the time to perform a reload from empty, taking into account mods.
	/// @param attackName The firing mode being queried
	/// @return The time in seconds to complete the reload.
	float GetReloadTime(std::string attackName);
	/// @brief Get the efficiency of ammo consumption for the weapon. The normal value is 0, where ammo is consumed at a normal rate. A value of 1 denotes perfect efficiency, and no ammo is consumed.
	/// @return
	float GetAmmoEfficiency();
};