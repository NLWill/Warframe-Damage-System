#pragma once
#include "src/Target/Faction.h"
#include "src/Target/HealthType.h"
#include "src/Mods/ModBase.h"
#include <map>
#include <string>
#include <utility>

class Target{
	public:
	Target();
	Target(int level, float maxHealth, float maxArmour, Faction faction, HealthType healthType, std::map<std::string, std::pair<float, bool>> bodyPartMultipliers, std::vector<Mod *> innateModUpgrades);
	Target(Target &other);

	int level;
	float currentHealth;
	float maxHealth;
	float GetArmour();
	void SetArmour(float value);
	Faction faction;
	HealthType healthType;
	std::vector<Mod *> innateUpgrades;
	float GetBodyPartMultiplier(std::string partName);
	bool IsBodyPartWeakPoint(std::string partName);
	void AddBodyPartMultiplier(std::string partName, float multiplier, bool isWeakPoint);

	std::vector<ProcType> afflictedStatusEffects;

	private:
	float currentArmour;
	float maxArmour;
	std::map<std::string, std::pair<float, bool>> bodyPartMultipliers;
};