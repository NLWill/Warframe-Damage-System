#pragma once
#include "src/Target/Faction.h"
#include <map>
#include <string>
#include <utility>

class Target{
	public:
	Target();
	Target(int level, float maxHealth, float maxArmour, Faction faction, std::map<std::string, std::pair<float, bool>> bodyPartMultipliers);
	Target(Target &other);

	int level;
	float currentHealth;
	float maxHealth;
	float GetArmour();
	void SetArmour(float value);
	Faction faction;
	float GetBodyPartMultiplier(std::string partName);
	bool IsBodyPartWeakPoint(std::string partName);
	void AddBodyPartMultiplier(std::string partName, float multiplier, bool isWeakPoint);

	private:
	float currentArmour;
	float maxArmour;
	std::map<std::string, std::pair<float, bool>> bodyPartMultipliers;
};