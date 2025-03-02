#pragma once
#include "src/Weapons/WeaponData.h"
#include <string>
#include <vector>
#include "src/Mods/ModManagerInterface.h"
#include "src/Target/Target.h"

class Weapon
{
public:
	Weapon(WeaponData &weaponData);
	~Weapon();
	WeaponData weaponData;

	ModManagerInterface *modManager;

	std::vector<ModEffectBase *> GetAllWeaponModEffects(ModUpgradeType upgradeType);

	/// @brief Fire the weapon. This sends the whole attack through the damage pipeline, as well as any sub-attacks to find the total damage dealt to the target.
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return A pair of floats, for the direct damage from bullet impact as well as damage over time from status effects
	std::pair<float, float> Fire(std::string attackName, Target &target, std::string targetBodyPart);

	/// @brief Calculate the average damage that the weapon would achieve against the target per trigger pull
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return A pair of floats, for the direct damage from bullet impact as well as damage over time from status effects
	std::pair<float, float> GetAverageDamagePerShot(std::string attackName, Target &target, std::string targetBodyPart);

	/// @brief Calculate the average DPS the weapon will achieve without taking reloading into account
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return The total DPS achieved including direct hits and status effects
	float GetAverageBurstDPS(std::string attackName, Target &target, std::string targetBodyPart);

	/// @brief Calculate the average DPS the weapon will achieve over a sustained period of time, taking into account the time spent reloading
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return The total DPS achieved including direct hits and status effects
	float GetAverageSustainedDPS(std::string attackName, Target &target, std::string targetBodyPart);

	float GetFireRate(std::string attackName);
	float GetChargeTime(std::string attackName);
	int GetMagazineCapacity();
	float GetReloadTime(std::string attackName);
	float GetAmmoEfficiency();
};