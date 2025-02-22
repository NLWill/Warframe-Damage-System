#include "src/Weapons/DamageType.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Weapons/WeaponFactory.h"
#include "DamageInstance.h"

DamageInstance::DamageInstance()
{
	weapon = WeaponFactory::GetNullWeapon();
	attackName = "Normal Attack";
	target = new Target();
	targetBodyPart = "Body";

	damageData = weapon->weaponData.firingModes.at(attackName).attackData.damageData;
	double totalDamage = damageData.damageTotal;
	for (auto damageTypeProportion : damageData.percentageDamageDistribution)
	{
		damageValues.push_back(DamageValue(damageTypeProportion.first, damageTypeProportion.second * totalDamage));
	}
}

DamageInstance::DamageInstance(const DamageInstance &other)
{
	damageValues = other.damageValues;
	statusEffects = other.statusEffects;
	critTier = other.critTier;

	weapon = other.weapon;
	damageData = other.damageData;
	target = other.target;
	targetBodyPart = other.targetBodyPart;

	moddedCriticalChance = other.moddedCriticalChance;
	moddedCriticalDamage = other.moddedCriticalDamage;
	moddedStatusChance = other.moddedStatusChance;
	moddedStatusDamageMultiplier = other.moddedStatusDamageMultiplier;
}

DamageInstance::DamageInstance(Weapon &_weapon, std::string _attackName, DamageData _damageData, Target &_target, std::string targetBodyPart)
{
	weapon = &_weapon;
	attackName = _attackName;
	damageData = _damageData;
	target = &_target;
	this->targetBodyPart = targetBodyPart;

	double totalDamage = damageData.damageTotal;
	for (auto damageTypeProportion : damageData.percentageDamageDistribution)
	{
		damageValues.push_back(DamageValue(damageTypeProportion.first, damageTypeProportion.second * totalDamage));
	}

	moddedCriticalChance = damageData.critChance;
	moddedCriticalDamage = damageData.critDamage;
	moddedStatusChance = damageData.statusChance;
	moddedStatusDamageMultiplier = 1;
}

DamageInstance &DamageInstance::operator*(const float &mult)
{
	return *this *= mult;
}

DamageInstance &DamageInstance::operator=(const DamageInstance &other)
{
	damageValues = std::vector<DamageValue>(other.damageValues);
	statusEffects = std::vector<ProcType>(other.statusEffects);
	critTier = other.critTier;
	return *this;
}

DamageInstance &DamageInstance::operator*=(const float &mult)
{
	for (int i = 0; i < damageValues.size(); i++)
	{
		damageValues[i] *= mult;
	}

	return *this;
}

std::vector<ModEffectBase *> DamageInstance::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<ModEffectBase *> relevantEffects = {};

	auto weaponEffects = weapon->GetAllWeaponModEffects(upgradeType);
	relevantEffects.insert(relevantEffects.end(), weaponEffects.begin(), weaponEffects.end());

	for (auto mod : target->innateUpgrades)
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

	// ServiceLocator::GetLogger().Log("For UpgradeType: " + std::to_string(upgradeType) + " the length of modEffects is " + std::to_string(relevantEffects.size()));

	return relevantEffects;
}

float DamageInstance::GetTotalDamage()
{
	float sum = 0;
	for (int i = 0; i < damageValues.size(); i++)
	{
		sum += damageValues[i].value;
	}
	return sum;
}

std::vector<DamageValue> DamageInstance::GetDamageValues()
{
	return damageValues;
}

void DamageInstance::AddDamageValue(DamageValue damageValue)
{
	if (damageValue.value > 0 && damageValue.damageType != DamageType::DT_ANY)
	{
		damageValues.push_back(damageValue);
	}
}

std::vector<ProcType> DamageInstance::GetStatusEffects()
{
	return statusEffects;
}

void DamageInstance::AddStatusEffect(ProcType statusEffect)
{
	if (statusEffect != ProcType::PT_NONE)
	{
		statusEffects.push_back(statusEffect);
	}
}

std::string DamageInstance::GetAttackName()
{
	return attackName;
}

DamageData DamageInstance::GetDamageData()
{
	return damageData;
}

std::string DamageInstance::GetWeaponCategory()
{
	return weapon->weaponData.parent;
}

float DamageInstance::GetFireRate()
{
	return weapon->weaponData.firingModes.at(attackName).fireRate;
}

float DamageInstance::GetCriticalChance()
{
	return moddedCriticalChance;
}

float DamageInstance::GetCriticalDamage()
{
	return moddedCriticalDamage;
}

float DamageInstance::GetCriticalTier()
{
	return critTier;
}

float DamageInstance::GetStatusChance()
{
	return moddedStatusChance;
}

float DamageInstance::GetStatusDamageMultiplier()
{
	return moddedStatusDamageMultiplier;
}

float DamageInstance::GetStatusDurationMultiplier()
{
	return moddedStatusDurationMultiplier;
}

int DamageInstance::GetModSetCount(std::string setName)
{
	int modSetCount = 0;
	if (setName == "")
		return 0;

	for (int i = 0; i < weapon->modManager->GetModSlotCount(); i++)
	{
		if (weapon->modManager->GetMod(i) == nullptr)
		{
			continue;
		}

		if (weapon->modManager->GetMod(i)->modSet == setName)
		{
			modSetCount++;
		}
	}

	return modSetCount;
}

int DamageInstance::GetTargetLevel()
{
	return target->level;
}

float DamageInstance::GetTargetMaxHealth()
{
	return target->maxHealth;
}

float DamageInstance::GetTargetCurrentHealth()
{
	return target->currentHealth;
}

Faction DamageInstance::GetTargetFaction()
{
	return target->faction;
}

bool DamageInstance::IsTargetHitzoneWeakPoint()
{
	return target->IsBodyPartWeakPoint(targetBodyPart);
}

bool DamageInstance::IsTargetHitzoneHeadshot()
{
	return targetBodyPart == "Head";
}

float DamageInstance::GetTargetHitzoneMultiplier()
{
	return target->GetBodyPartMultiplier(targetBodyPart);
}

float DamageInstance::GetTargetArmour()
{
	return target->GetArmour();
}

std::vector<ProcType> DamageInstance::GetStatusEffectsOnTarget()
{
	return target->afflictedStatusEffects;
}
