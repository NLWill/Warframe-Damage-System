#pragma once
#include <memory>
#include "src/Weapons/WeaponData.h"
#include <string>
#include <vector>
#include "src/Mods/IModManager.h"
#include "src/Target/Target.h"

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

	// Struct handling equipping/removing mods and parsing values when needed.
	std::shared_ptr<IModManager> modManager;

	/// @brief Get a vector of ModEffects which affect the provided ModUpgradeType
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @return A vector of shared pointers to all mod effects which affect the associated ModUpgradeType
	std::vector<std::shared_ptr<IModEffect>> GetAllWeaponModEffects(ModUpgradeType upgradeType);

	/// @brief Fire the weapon. This sends the whole attack through the damage pipeline, as well as any sub-attacks to find the total damage dealt to the target.
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return A pair of floats, for the direct damage from bullet impact as well as damage over time from status effects
	std::pair<float, float> Fire(std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);

	/// @brief Calculate the average damage that the weapon would achieve against the target per trigger pull
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return A pair of floats, for the direct damage from bullet impact as well as damage over time from status effects
	std::pair<float, float> GetAverageDamagePerShot(std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);

	/// @brief Calculate the average DPS the weapon will achieve without taking reloading into account
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return The total DPS achieved including direct hits and status effects
	float GetAverageBurstDPS(std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);

	/// @brief Calculate the average DPS the weapon will achieve over a sustained period of time, taking into account the time spent reloading
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return The total DPS achieved including direct hits and status effects
	float GetAverageSustainedDPS(std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);

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