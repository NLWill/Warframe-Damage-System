#include "src/Weapons/Weapon.h"
#include "src/Mods/ModManager.h"
#include "src/DamagePipeline/FireInstance.h"
#include "src/DamagePipeline/MultishotProcess/MultishotProcess.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include <cmath>

#define DEBUG_WEAPON false
#if DEBUG_WEAPON
#include "src/Services/ServiceLocator.h"
#endif

Weapon::Weapon(WeaponData &weaponData, shared_ptr<IModManager> modManager) : weaponData{weaponData}
{
	this->modManager = modManager;
}

shared_ptr<Weapon> Weapon::GetPtr()
{
	return shared_from_this();
}

std::vector<shared_ptr<IModEffect>> Weapon::GetAllWeaponModEffects(ModUpgradeType upgradeType)
{
	// First get all mods equipped on the weapon
	auto relevantEffects = modManager->GetAllModEffects(upgradeType);

	// Then process mod effects innate on the weapon
	for (auto mod : weaponData.defaultSlottedUpgrades)
	{
		if (mod == nullptr)
		{
			continue;
		}

		for (auto modEffect : mod->GetModEffects())
		{
			if (modEffect->GetUpgradeType() == upgradeType)
			{
				relevantEffects.push_back(modEffect);
			}
		}
	}

	// Get all modEffects from the incarnon evolutions and append to the complete vector of effects
	auto incarnonEffects = weaponData.incarnonUpgrades.GetAllModEffects(upgradeType);
	relevantEffects.insert(relevantEffects.end(), incarnonEffects.begin(), incarnonEffects.end());

	return relevantEffects;
}

std::pair<float, float> Weapon::Fire(std::string attackName, shared_ptr<Target> target, std::string targetBodyPart)
{
#if DEBUG_WEAPON
	ServiceLocator::GetLogger().Log("Starting Fire process");
#endif

	// Check that the weapon contains the firing mode with the associated name
	if (!weaponData.IsValidFiringMode(attackName))
	{
		return {0, 0};
	}

	// Calculate the multishot of the weapon
	auto fireInstance = make_shared<FireInstance>(GetPtr(), attackName);
#if DEBUG_WEAPON
	ServiceLocator::GetLogger().Log("Created FireInstance");
#endif

	//-> Multishot
	MultishotProcess::EvaluateMultishotMods(fireInstance);
	int rolledMultishot = MultishotProcess::RollForMultishot(fireInstance); // Rolled multishot takes into account the base multishot of the weapon, and sub attacks should be duplicated by this value
#if DEBUG_WEAPON
	ServiceLocator::GetLogger().Log("Rolled multishot of " + std::to_string(rolledMultishot));
#endif

	// Alias the firing mode selected from the attackName
	FiringMode &firingMode = weaponData.firingModes[attackName];
#if DEBUG_WEAPON
	ServiceLocator::GetLogger().Log("Obtained FiringMode");
#endif

	if (firingMode.combineMultishotIntoSingleInstance)
	{
		// For continuous weapons that handle multishot differently,
		// Create a single damageInstance and scale its damage and status chance proportionately to the rolled multishot
		// This has been tested extensively and this even happens for continuous weapons with innate multishot e.g. Quanta Vandal
		fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, firingMode.attackData.damageData, target, targetBodyPart));
		for (DamageData damageData : firingMode.attackData.subAttacks)
		{
			for (size_t j = 0; j < damageData.multishot; j++)
			{
				fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, damageData, target, targetBodyPart));
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
			fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, firingMode.attackData.damageData, target, targetBodyPart));
			for (DamageData damageData : firingMode.attackData.subAttacks)
			{
				for (size_t j = 0; j < damageData.multishot; j++)
				{
					fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, damageData, target, targetBodyPart));
				}
			}
		}
	}
#if DEBUG_WEAPON
	ServiceLocator::GetLogger().Log("Created DamageInstances");
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

std::pair<float, float> Weapon::GetAverageDamagePerShot(std::string attackName, shared_ptr<Target> target, std::string targetBodyPart)
{
	// Check that the weapon contains the firing mode with the associated name
	if (!weaponData.IsValidFiringMode(attackName))
	{
		return {0, 0};
	}

	// Calculate the multishot of the weapon (the number of bullets fired per trigger pull)
	auto fireInstance = make_shared<FireInstance>(GetPtr(), attackName);

	// Alias the firing mode selected from the attackName
	FiringMode &firingMode = weaponData.firingModes[attackName];

	//-> Multishot
	MultishotProcess::EvaluateMultishotMods(fireInstance);
	float moddedMultishot = fireInstance->moddedMultishot;

	if (firingMode.combineMultishotIntoSingleInstance)
	{
		// For continuous weapons that handle multishot differently,
		// Create a single damageInstance and scale its damage and status chance proportionately to the rolled multishot
		// This has been tested extensively and this even happens for continuous weapons with innate multishot e.g. Quanta Vandal
		fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, firingMode.attackData.damageData, target, targetBodyPart));
		for (DamageData damageData : firingMode.attackData.subAttacks)
		{
			for (size_t j = 0; j < damageData.multishot; j++)
			{
				fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, damageData, target, targetBodyPart, true));
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
		fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, firingMode.attackData.damageData, target, targetBodyPart, true));
		for (DamageData damageData : firingMode.attackData.subAttacks)
		{
			for (size_t j = 0; j < damageData.multishot; j++)
			{
				fireInstance->damageInstances.push_back(make_shared<DamageInstance>(GetPtr(), attackName, damageData, target, targetBodyPart, true));
			}
		}
	}

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

float Weapon::GetAverageBurstDPS(std::string attackName, shared_ptr<Target> target, std::string targetBodyPart)
{
	auto result = GetAverageDamagePerShot(attackName, target, targetBodyPart);
	float avgDmgPerShot = result.first + result.second;

	float fireRate = GetFireRate(attackName);
	float chargeTime = GetChargeTime(attackName);

	float effectiveFireRate = 1 / (chargeTime + (1 / fireRate));

	int magazineCapacity = GetMagazineCapacity();
	float ammoEfficiency = GetAmmoEfficiency();
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

float Weapon::GetAverageSustainedDPS(std::string attackName, shared_ptr<Target> target, std::string targetBodyPart)
{
	auto result = GetAverageDamagePerShot(attackName, target, targetBodyPart);
	float avgDmgPerShot = result.first + result.second;

	float fireRate = GetFireRate(attackName);
	float chargeTime = GetChargeTime(attackName);

	float effectiveFireRate = 1 / (chargeTime + (1 / fireRate));
	float avgBurstDPS = avgDmgPerShot * effectiveFireRate;

	int magazineCapacity = GetMagazineCapacity();
	float ammoEfficiency = GetAmmoEfficiency();
	if (ammoEfficiency >= 1)
	{
		// 100% ammo efficiency
		return avgBurstDPS;
	}
	float numberOfShotsPerMag = magazineCapacity / (1 - ammoEfficiency);
	float reloadTime = GetReloadTime(attackName);
	float timeToEmptyMagazine = numberOfShotsPerMag / effectiveFireRate;

	float proportionOfTimeSpentShooting = timeToEmptyMagazine / (timeToEmptyMagazine + reloadTime);

	return proportionOfTimeSpentShooting * avgBurstDPS;
}

float Weapon::GetFireRate(std::string attackName)
{
	float fireRate = weaponData.firingModes[attackName].fireRate;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = attackName;

		fireRate = DamagePipeline::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_FIRE_RATE, fireRate);
		fireRate = max(fireRate, (float)0.05); // Limit fire rate so that it cannot be below 0.05
	}
	return fireRate;
}

float Weapon::GetChargeTime(std::string attackName)
{
	float baseChargeTime = 0;
	float chargeTime = 0;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	if (chargeTime > 0)
	{
		auto tempDamageInstance = make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = attackName;

		// Charge time is inversely scaled by fire rate, so first convert to charge rate
		float chargeRate = 1 / baseChargeTime;
		chargeRate = DamagePipeline::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_FIRE_RATE, chargeRate);
		chargeTime = 1 / chargeRate;
		chargeTime = min(chargeTime, 10 * baseChargeTime); // Charge time cannot be longer than 10x base value
	}
	return chargeTime;
}

int Weapon::GetMagazineCapacity()
{
	int numberOfShotsPerMag = weaponData.ammoClipSize;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = "";

		numberOfShotsPerMag = std::round(DamagePipeline::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_MAGAZINE_CAPACITY, numberOfShotsPerMag));
		numberOfShotsPerMag = std::max(numberOfShotsPerMag, 1); // Magsize cannot go below 1
	}
	return numberOfShotsPerMag;
}

float Weapon::GetReloadTime(std::string attackName)
{
	float reloadTime = weaponData.firingModes[attackName].reloadTime;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = attackName;

		// Reload time is inversely scaled by reload speed, so get the inverse first
		float reloadSpeed = 1 / reloadTime;
		reloadSpeed = DamagePipeline::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_RELOAD_SPEED, reloadSpeed);
		reloadTime = 1 / reloadSpeed;
	}
	return reloadTime;
}

float Weapon::GetAmmoEfficiency()
{
	float ammoEfficiency;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = "";

		// Calculate the multiplicative factor scaling amount of ammo consumed
		float ammoConsumeRate = DamagePipeline::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_AMMO_CONSUME_RATE, 1);
		// Take 1 - consume rate to get the efficiency factor
		ammoEfficiency = 1 - ammoConsumeRate;
		ammoEfficiency = std::min(ammoEfficiency, (float)1); // Ensure the weapon cannot regain ammo by having over 100% efficiency
	}
	return ammoEfficiency;
}
