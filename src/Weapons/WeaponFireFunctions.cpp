#include "src/Weapons/WeaponFireFunctions.h"
#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"

#define DEBUG_WEAPON_FIRE_FUNCTIONS false
#if DEBUG_WEAPON_FIRE_FUNCTIONS
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#endif

std::pair<float, float> WeaponFireFunctions::Fire(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart)
{
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Starting Fire process");
#endif

	// Check that the weapon contains the firing mode with the associated name
	if (!weapon->weaponData.IsValidFiringMode(attackName))
	{
		return {0, 0};
	}

	// Calculate the multishot of the weapon
	auto fireInstance = std::make_shared<FireInstance>(weapon, attackName);
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Created FireInstance");
#endif

	//-> Multishot
	MultishotProcess::EvaluateMultishotMods(fireInstance);
	int rolledMultishot = MultishotProcess::RollForMultishot(fireInstance); // Rolled multishot takes into account the base multishot of the weapon, and sub attacks should be duplicated by this value
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Rolled multishot of " + std::to_string(rolledMultishot));
#endif

	// Alias the firing mode selected from the attackName
	FiringMode &firingMode = weapon->weaponData.firingModes[attackName];
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Obtained FiringMode");
#endif

	if (firingMode.combineMultishotIntoSingleInstance)
	{
		// For continuous weapons that handle multishot differently,
		// Create a single damageInstance and scale its damage and status chance proportionately to the rolled multishot
		// This has been tested extensively and this even happens for continuous weapons with innate multishot e.g. Quanta Vandal
		fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, firingMode.attackData.damageData, target, targetBodyPart));
		for (DamageData damageData : firingMode.attackData.subAttacks)
		{
			for (size_t j = 0; j < damageData.multishot; j++)
			{
				fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, damageData, target, targetBodyPart));
			}
		}

		for (size_t i = 0; i < fireInstance->damageInstances.size(); i++)
		{
			*fireInstance->damageInstances[i] *= rolledMultishot;
			fireInstance->damageInstances[i]->damageData.statusChance *= rolledMultishot / firingMode.attackData.damageData.multishot;
		}
	}
	else
	{
		// For normal bullet weapons, create the number of damageInstances equal to the rolled multishot
		for (int i = 0; i < rolledMultishot; i++)
		{
			fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, firingMode.attackData.damageData, target, targetBodyPart));
			for (DamageData damageData : firingMode.attackData.subAttacks)
			{
				for (size_t j = 0; j < damageData.multishot; j++)
				{
					fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, damageData, target, targetBodyPart));
				}
			}
		}
	}
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Created DamageInstances");
#endif

	float totalDirectDamage = 0;
	float totalDOTDamage = 0;
	for (size_t i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		auto result = DamagePipeline::RunDamagePipeline(fireInstance->damageInstances[i]);
		totalDirectDamage += result.first;
		totalDOTDamage += result.second;
	}

	return {totalDirectDamage, totalDOTDamage};
}

std::pair<float, float> WeaponFireFunctions::GetAverageDamagePerShot(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart)
{
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Starting AverageDamagePerShot process");
#endif
	// Check that the weapon contains the firing mode with the associated name
	if (!weapon->weaponData.IsValidFiringMode(attackName))
	{
		return {0, 0};
	}

	// Calculate the multishot of the weapon (the number of bullets fired per trigger pull)
	auto fireInstance = std::make_shared<FireInstance>(weapon, attackName);
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Created FireInstance");
#endif

	//-> Multishot
	MultishotProcess::EvaluateMultishotMods(fireInstance);
	float moddedMultishot = fireInstance->moddedMultishot;
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Modded multishot = " + std::to_string(moddedMultishot));
#endif

	// Alias the firing mode selected from the attackName
	FiringMode &firingMode = weapon->weaponData.firingModes[attackName];
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Obtained FiringMode");
#endif

	if (firingMode.combineMultishotIntoSingleInstance)
	{
		// For continuous weapons that handle multishot differently,
		// Create a single damageInstance and scale its damage and status chance proportionately to the rolled multishot
		// This has been tested extensively and this even happens for continuous weapons with innate multishot e.g. Quanta Vandal
		fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, firingMode.attackData.damageData, target, targetBodyPart));
		for (DamageData damageData : firingMode.attackData.subAttacks)
		{
			for (size_t j = 0; j < damageData.multishot; j++)
			{
				fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, damageData, target, targetBodyPart, true));
			}
		}

		for (size_t i = 0; i < fireInstance->damageInstances.size(); i++)
		{
			*fireInstance->damageInstances[i] *= moddedMultishot;
			fireInstance->damageInstances[i]->damageData.statusChance *= moddedMultishot / firingMode.attackData.damageData.multishot;
		}
	}
	else
	{
		// For normal bullet weapons, create the number of damageInstances equal to the rolled multishot
		fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, firingMode.attackData.damageData, target, targetBodyPart, true));
		for (DamageData damageData : firingMode.attackData.subAttacks)
		{
			for (size_t j = 0; j < damageData.multishot; j++)
			{
				fireInstance->damageInstances.push_back(std::make_shared<DamageInstance>(weapon, attackName, damageData, target, targetBodyPart, true));
			}
		}
	}
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Created DamageInstances");
#endif

	// Run each damage instance through the damage pipeline to find the total average damage dealt
	float totalDirectDamage = 0;
	float totalDOTDamage = 0;
	for (size_t i = 0; i < fireInstance->damageInstances.size(); i++)
	{
		auto result = DamagePipeline::RunAverageDamagePipeline(fireInstance->damageInstances[i]);
		totalDirectDamage += result.first;
		totalDOTDamage += result.second;
	}

	// For continuous weapons, the multishot was scaled into the base damage and status chance
	// For normal weapons, the total damage shall just be multiplied by the multishot
	if (!firingMode.combineMultishotIntoSingleInstance)
	{
		totalDirectDamage *= moddedMultishot;
		totalDOTDamage *= moddedMultishot;
	}

	return {totalDirectDamage, totalDOTDamage};
}

float WeaponFireFunctions::GetAverageBurstDPS(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart)
{
	auto result = GetAverageDamagePerShot(weapon, attackName, target, targetBodyPart);
	float avgDmgPerShot = result.first + result.second;
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Got average damage per shot: " + std::to_string(avgDmgPerShot));
#endif

	float fireRate = weapon->GetFireRate(attackName);
	float chargeTime = weapon->GetChargeTime(attackName);

	float effectiveFireRate = 1 / (chargeTime + (1 / fireRate));
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Effective fire rate = " + std::to_string(effectiveFireRate));
#endif

	int magazineCapacity = weapon->GetMagazineCapacity();
	float ammoEfficiency = weapon->GetAmmoEfficiency();
	if (ammoEfficiency >= 1)
	{
		// 100% ammo efficiency
		return avgDmgPerShot * effectiveFireRate;
	}

	float totalDmgInMagazine = magazineCapacity / (1 - ammoEfficiency) * avgDmgPerShot;

	float timeToEmptyMagazine = magazineCapacity / ((1 - ammoEfficiency) * effectiveFireRate);
	if (timeToEmptyMagazine < 1)
	{
		return totalDmgInMagazine;
	}

	float avgBurstDPS = totalDmgInMagazine / timeToEmptyMagazine;
	return avgBurstDPS;
}

float WeaponFireFunctions::GetAverageSustainedDPS(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart)
{
	auto result = GetAverageDamagePerShot(weapon, attackName, target, targetBodyPart);
	float avgDmgPerShot = result.first + result.second;
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Got average damage per shot: " + std::to_string(avgDmgPerShot));
#endif

	float fireRate = weapon->GetFireRate(attackName);
	float chargeTime = weapon->GetChargeTime(attackName);

	float effectiveFireRate = 1 / (chargeTime + (1 / fireRate));
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Effective fire rate = " + std::to_string(effectiveFireRate));
#endif
	float avgBurstDPS = avgDmgPerShot * effectiveFireRate;
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Average Burst DPS = " + std::to_string(avgBurstDPS));
#endif

	int magazineCapacity = weapon->GetMagazineCapacity();
	float ammoEfficiency = weapon->GetAmmoEfficiency();
	if (ammoEfficiency >= 1)
	{
		// 100% ammo efficiency
		return avgBurstDPS;
	}
	float numberOfShotsPerMag = magazineCapacity / (1 - ammoEfficiency);
	float reloadTime = weapon->GetReloadTime(attackName);
	float timeToEmptyMagazine = numberOfShotsPerMag / effectiveFireRate;

	float proportionOfTimeSpentShooting = timeToEmptyMagazine / (timeToEmptyMagazine + reloadTime);
#if DEBUG_WEAPON_FIRE_FUNCTIONS
	ServiceLocator::GetService<ILogService>()->Log("Proportion of time spent shooting = " + std::to_string(proportionOfTimeSpentShooting));
#endif

	return proportionOfTimeSpentShooting * avgBurstDPS;
}
