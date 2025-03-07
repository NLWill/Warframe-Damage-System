#pragma once
#include <memory>
#include <string>
#include "src/Weapons/Weapon.h"
#include "src/Target/Target.h"

class WeaponFireFunctions
{
public:
	/// @brief Fire the weapon. This sends the whole attack through the damage pipeline, as well as any sub-attacks to find the total damage dealt to the target.
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return A pair of floats, for the direct damage from bullet impact as well as damage over time from status effects
	static std::pair<float, float> Fire(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);

	/// @brief Calculate the average damage that the weapon would achieve against the target per trigger pull
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return A pair of floats, for the direct damage from bullet impact as well as damage over time from status effects
	static std::pair<float, float> GetAverageDamagePerShot(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);

	/// @brief Calculate the average DPS the weapon will achieve without taking reloading into account
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return The total DPS achieved including direct hits and status effects
	static float GetAverageBurstDPS(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);

	/// @brief Calculate the average DPS the weapon will achieve over a sustained period of time, taking into account the time spent reloading
	/// @param attackName The name of the desired firing mode
	/// @param target The enemy target that will be hit by the bullet
	/// @param targetBodyPart The string name for the body part to be hit
	/// @return The total DPS achieved including direct hits and status effects
	static float GetAverageSustainedDPS(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart);
};
