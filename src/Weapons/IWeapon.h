#pragma once
#include <string>
#include "src/Weapons/WeaponData.h"

class IWeapon
{
public:
	/// @brief Get the weapon data struct from the weapon
	/// @return A reference to the weapon data struct
	virtual WeaponData &GetWeaponData() = 0;
	/// @brief Get the modded fire rate of the weapon
	/// @param attackName The firing mode being queried
	/// @return Returns the number of shots per second output by the weapon
	virtual float GetFireRate(std::string attackName) = 0;
	/// @brief Get the time to fully charge the weapon, taking into accout mods. For most non-charge-based weapons, this value will be 0.
	/// @param attackName The firing mode being queried
	/// @return
	virtual float GetChargeTime(std::string attackName) = 0;
	/// @brief Get the modded magazine capacity of the weapon
	/// @return
	virtual int GetMagazineCapacity() = 0;
	/// @brief Get the time to perform a reload from empty, taking into account mods.
	/// @param attackName The firing mode being queried
	/// @return The time in seconds to complete the reload.
	virtual float GetReloadTime(std::string attackName) = 0;
	/// @brief Get the efficiency of ammo consumption for the weapon. The normal value is 0, where ammo is consumed at a normal rate. A value of 1 denotes perfect efficiency, and no ammo is consumed.
	/// @return
	virtual float GetAmmoEfficiency() = 0;
};