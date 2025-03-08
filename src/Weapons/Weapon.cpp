#include "src/Weapons/Weapon.h"
#include "src/Mods/ModManager.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/DamagePipeline/ModProcessingFunctions.h"
#include <cmath>

#define DEBUG_WEAPON true
#if DEBUG_WEAPON
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#endif

Weapon::Weapon(WeaponData &weaponData, std::shared_ptr<IModManager> modManager) : weaponData{weaponData}
{
	this->modManager = modManager;
}

std::shared_ptr<Weapon> Weapon::GetPtr()
{
	return shared_from_this();
}

std::vector<std::shared_ptr<IModEffect>> Weapon::GetAllWeaponModEffects(ModUpgradeType upgradeType)
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

float Weapon::GetFireRate(std::string attackName)
{
	float fireRate = weaponData.firingModes[attackName].fireRate;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = std::make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = attackName;

		fireRate = ModProcessingFunctions::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_FIRE_RATE, fireRate);
		fireRate = std::max(fireRate, (float)0.05); // Limit fire rate so that it cannot be below 0.05
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
		auto tempDamageInstance = std::make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = attackName;

		// Charge time is inversely scaled by fire rate, so first convert to charge rate
		float chargeRate = 1 / baseChargeTime;
		chargeRate = ModProcessingFunctions::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_FIRE_RATE, chargeRate);
		chargeTime = 1 / chargeRate;
		chargeTime = std::min(chargeTime, 10 * baseChargeTime); // Charge time cannot be longer than 10x base value
	}
	return chargeTime;
}

int Weapon::GetMagazineCapacity()
{
	int numberOfShotsPerMag = weaponData.ammoClipSize;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = std::make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = "";

		numberOfShotsPerMag = std::round(ModProcessingFunctions::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_CLIP_MAX, numberOfShotsPerMag));
		numberOfShotsPerMag = std::max(numberOfShotsPerMag, 1); // Magsize cannot go below 1
	}
	return numberOfShotsPerMag;
}

float Weapon::GetReloadTime(std::string attackName)
{
	float reloadTime = weaponData.firingModes[attackName].reloadTime;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = std::make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = attackName;

		// Reload time is inversely scaled by reload speed, so get the inverse first
		float reloadSpeed = 1 / reloadTime;
		reloadSpeed = ModProcessingFunctions::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_RELOAD_SPEED, reloadSpeed);
		reloadTime = 1 / reloadSpeed;
	}
	return reloadTime;
}

float Weapon::GetAmmoEfficiency()
{
	float ammoEfficiency;
	// Create a temporary damageInstance to feed into the modEffects to allow querying of mod values
	{
		auto tempDamageInstance = std::make_shared<DamageInstance>();
		tempDamageInstance->weapon = GetPtr();
		tempDamageInstance->attackName = "";

		// Calculate the multiplicative factor scaling amount of ammo consumed
		float ammoConsumeRate = ModProcessingFunctions::EvaluateAndApplyModEffects(tempDamageInstance, ModUpgradeType::WEAPON_AMMO_CONSUME_RATE, 1);
		// Take 1 - consume rate to get the efficiency factor
		ammoEfficiency = 1 - ammoConsumeRate;
		ammoEfficiency = std::min(ammoEfficiency, (float)1); // Ensure the weapon cannot regain ammo by having over 100% efficiency
	}
	return ammoEfficiency;
}
