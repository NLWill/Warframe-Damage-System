#include "src/Weapons/DamageType.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Weapons/WeaponFactory.h"
#include <algorithm>

#define DEBUG_DAMAGE_INSTANCE false
#if DEBUG_DAMAGE_INSTANCE
#include "src/Services/ServiceLocator.h"
#endif

DamageInstance::DamageInstance() : weapon{WeaponFactory::GetNullWeapon()}
{
	attackName = "Normal Attack";
	target = make_shared<Target>();
	targetBodyPart = "Body";

	damageData = weapon->weaponData.firingModes.at(attackName).attackData.damageData;
	double totalDamage = damageData.damageTotal;
	baseDamageValue = totalDamage;
	for (auto damageTypeProportion : damageData.percentageDamageDistribution)
	{
		damageValues.push_back(DamageValue(damageTypeProportion.first, damageTypeProportion.second * totalDamage));
	}
	calculateAverageDamage = false;
}

DamageInstance::DamageInstance(const DamageInstance &other) : enable_shared_from_this<DamageInstance>(other), weapon{other.weapon}
{
	damageValues = other.damageValues;
	baseDamageValue = other.baseDamageValue;
	statusEffects = other.statusEffects;
	critTier = other.critTier;

	damageData = other.damageData;
	target = other.target;
	targetBodyPart = other.targetBodyPart;

	moddedCriticalChance = other.moddedCriticalChance;
	moddedCriticalDamage = other.moddedCriticalDamage;
	moddedStatusChance = other.moddedStatusChance;
	moddedStatusDamageMultiplier = other.moddedStatusDamageMultiplier;

	calculateAverageDamage = other.calculateAverageDamage;
}

DamageInstance::DamageInstance(shared_ptr<Weapon> _weapon, std::string _attackName, DamageData _damageData, shared_ptr<Target> _target, std::string targetBodyPart, bool averageCalculation) : weapon{_weapon}
{
	attackName = _attackName;
	damageData = _damageData;
	target = _target;
	this->targetBodyPart = targetBodyPart;

	double totalDamage = damageData.damageTotal;
	baseDamageValue = totalDamage;
	for (auto damageTypeProportion : damageData.percentageDamageDistribution)
	{
		damageValues.push_back(DamageValue(damageTypeProportion.first, damageTypeProportion.second * totalDamage));
	}

	moddedCriticalChance = FlaggedVariable<float>(damageData.critChance);
	moddedCriticalDamage = FlaggedVariable<float>(damageData.critDamage);
	moddedStatusChance = FlaggedVariable<float>(damageData.statusChance);
	moddedStatusDamageMultiplier = FlaggedVariable<float>(1);

	calculateAverageDamage = averageCalculation;
}

DamageInstance::~DamageInstance()
{
}

shared_ptr<DamageInstance> DamageInstance::GetPtr()
{
	return shared_from_this();
}

DamageInstance &DamageInstance::operator*(const float &mult)
{
	return *this *= mult;
}

DamageInstance &DamageInstance::operator=(const DamageInstance &other)
{
	baseDamageValue = other.baseDamageValue;
	elementalWeights = std::map<DamageType, float>(other.elementalWeights);
	damageValues = std::vector<DamageValue>(other.damageValues);
	statusEffects = std::vector<StatusEffect>(other.statusEffects);
	critTier = other.critTier;
	return *this;
}

DamageInstance &DamageInstance::operator*=(const float &mult)
{
	baseDamageValue *= mult;

	for (size_t i = 0; i < damageValues.size(); i++)
	{
		damageValues[i] *= mult;
	}

	return *this;
}

std::vector<shared_ptr<IModEffect>> DamageInstance::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<shared_ptr<IModEffect>> relevantEffects = {};

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
	for (size_t i = 0; i < damageValues.size(); i++)
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

std::map<DamageType, float> &DamageInstance::GetElementalWeights()
{
	return elementalWeights;
}

std::vector<ProcType> DamageInstance::GetTriggeredProcTypes()
{
	std::vector<ProcType> triggeredProcs;
	for (size_t i = 0; i < statusEffects.size(); i++)
	{
		triggeredProcs.push_back(statusEffects[i].procType);
	}

	return triggeredProcs;
}

void DamageInstance::AddStatusEffect(StatusEffect statusEffect)
{
	if (statusEffect.procType != ProcType::PT_NONE)
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
	return weapon->GetFireRate(attackName);
}

float DamageInstance::GetCriticalChance()
{
	return moddedCriticalChance.Get();
}

float DamageInstance::GetCriticalDamage()
{
	return moddedCriticalDamage.Get();
}

float DamageInstance::GetCriticalTier()
{
	return critTier.Get();
}

float DamageInstance::GetStatusChance()
{
	return moddedStatusChance.Get();
}

float DamageInstance::GetStatusDamageMultiplier()
{
	return moddedStatusDamageMultiplier.Get();
}

float DamageInstance::GetStatusDurationMultiplier()
{
	return moddedStatusDurationMultiplier.Get();
}

int DamageInstance::GetMagazineCapacity()
{
	return weapon->GetMagazineCapacity();
}

float DamageInstance::GetAmmoEfficiency()
{
	return weapon->GetAmmoEfficiency();
}

/*float DamageInstance::GetAverageStatusUptime(ProcType pt)
{
	// Copy the elemental weights into a new map that may be modified
	auto modifiedElementalWeights{GetElementalWeights()};

	// If the target is immune to the status effect, set the weight of it to 0
	for (auto damageTypeWeightPair : modifiedElementalWeights)
	{
		for (ProcType pt : target->immuneStatusEffects)
		{
			if (ProcType::GetProcTypeFromElement(damageTypeWeightPair.first) == pt)
			{
				modifiedElementalWeights[damageTypeWeightPair.first] = 0;
			}
		}
	}

	float totalElementalWeighting = 0;
	for (auto damageTypeWeightPair : modifiedElementalWeights)
	{
		totalElementalWeighting += damageTypeWeightPair.second;
	}

	// Iterate over all status effects that the weapon may apply and calculate the average uptime that each may have
	float statusChance = GetStatusChance();
	float fireRate = GetFireRate();
	float statusDurationModifier = GetStatusDurationMultiplier();

	// Calculate the probability of rolling a status per shot from the damage distribution
	std::map<ProcType, float> probabilityOfStatusPerShot;
	for (auto &procTypeWeight : modifiedElementalWeights)
	{
		probabilityOfStatusPerShot[ProcType::GetProcTypeFromElement(procTypeWeight.first)] += statusChance * procTypeWeight.second / totalElementalWeighting;
	}

	// Add guaranteed forced procs
	for (auto procType : GetDamageData().forcedProcs)
	{
		probabilityOfStatusPerShot[procType] += 1;
	}

	// Iterate over each status probability and calculate the average uptime that each will have with continuous firing, ignoring reloads
	float statusDuration = StatusEffect::GetStatusDuration(pt) * statusDurationModifier;

	// This is a statistical hack but it is quick and approximately accurate
	float avgShotsPerApplication = 1 / probabilityOfStatusPerShot[pt];
	float avgTimeBetweenProcs = avgShotsPerApplication / fireRate;
	float percentageUptime = statusDuration / avgTimeBetweenProcs;

	// Limit percentage uptime to realistic values, as multiple instances of the same proc do not count twice
	percentageUptime = std::clamp(percentageUptime, (float)0, (float)1);

	return percentageUptime;
}*/

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

std::string DamageInstance::GetTargetBodyPart()
{
	return targetBodyPart;
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
