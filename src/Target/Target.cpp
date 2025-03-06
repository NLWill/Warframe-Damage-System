#include "src/Target/Target.h"

Target::Target() : innateUpgrades({})
{
	level = 0;
	maxHealth = 1;
	currentHealth = maxHealth;
	maxArmour = 0;
	currentArmour = maxArmour;
	faction = Faction::NONE;
	healthType = HealthType::TENNO;
	bodyPartMultipliers = {{"Head", {3, true}}, {"Body", {1, false}}};
}

Target::Target(int level, float maxHealth, float maxArmour, Faction faction, HealthType healthType, std::map<std::string, std::pair<float, bool>> bodyPartMultipliers, std::vector<std::shared_ptr<Mod>> innateModUpgrades)
{
	this->level = level;
	this->maxHealth = maxHealth;
	this->currentHealth = maxHealth;
	this->maxArmour = maxArmour;
	this->currentArmour = maxArmour;
	this->faction = faction;
	this->healthType = healthType;
	this->bodyPartMultipliers = bodyPartMultipliers;
	innateUpgrades = innateModUpgrades;
}

Target::Target(Target &other) : innateUpgrades(other.innateUpgrades)
{
	level = other.level;
	maxHealth = other.maxHealth;
	currentHealth = other.currentHealth;
	maxArmour = other.maxArmour;
	currentArmour = other.currentArmour;
	faction = other.faction;
	bodyPartMultipliers = other.bodyPartMultipliers;
}

float Target::GetArmour()
{
	return currentArmour;
}

void Target::SetArmour(float value)
{
	currentArmour = std::max(value, (float)0);
}

float Target::GetBodyPartMultiplier(std::string partName)
{
	if (bodyPartMultipliers.count(partName) > 0)
	{
		return bodyPartMultipliers[partName].first;
	}
	else
		return 1;
}

bool Target::IsBodyPartWeakPoint(std::string partName)
{
	if (bodyPartMultipliers.count(partName) > 0)
	{
		return bodyPartMultipliers[partName].second;
	}
	else
		return false;
}

void Target::AddBodyPartMultiplier(std::string partName, float multiplier, bool isWeakPoint)
{
	bodyPartMultipliers[partName] = {multiplier, isWeakPoint};
}
