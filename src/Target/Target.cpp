#include "src/Target/Target.h"

Target::Target()
{
	level = 0;
	maxHealth = 1;
	currentHealth = maxHealth;
	maxArmour = 0;
	currentArmour = maxArmour;
	faction = Faction::FAC_NONE;
	bodyPartMultipliers = {};
}

Target::Target(int level, float maxHealth, float maxArmour, Faction faction, std::map<std::string, std::pair<float, bool>> bodyPartMultipliers)
{
	this->level = level;
	this->maxHealth = maxHealth;
	this->currentHealth = maxHealth;
	this->maxArmour = maxArmour;
	this->currentArmour = maxArmour;
	this->faction = faction;
	this->bodyPartMultipliers = bodyPartMultipliers;
}

Target::Target(Target &other)
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
