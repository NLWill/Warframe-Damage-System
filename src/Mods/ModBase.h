#pragma once
#include <vector>
#include <string>
#include "src/Mods/IModEffect.h"
#include "src/Mods/ModPolarity.h"
#include "src/Mods/ModSlotType.h"

class Mod
{
public:
	Mod();
	Mod(std::string name,
		std::string weaponClass,
		ModPolarity polarity,
		int rank,
		int maxRank,
		int baseCapacityDrain,
		std::vector<std::shared_ptr<IModEffect>> &modEffects);
	~Mod();
	std::string name;
	int id;
	std::vector<std::string> compatabilityTags;	  // List of features that a weapon must fulfil to be allowed to equip the mod
	std::vector<std::string> incompatabilityTags; // List of tags that invalidate a weapon from equipping a mod e.g. CRPBOW for Lenz
	std::string itemCompatability;				  // The group of weapons that this mod is intended for e.g. rifles or shotguns
	std::string weaponClass;
	ModPolarity polarity;
	ModSlotType slotType; // Normal/Aura/Exilus/Arcane etc.
	bool slotted;
	int rank;
	int maxRank;
	int baseCapacityDrain;
	int GetCurrentCapacityDrain();
	std::vector<std::shared_ptr<IModEffect>> GetModEffects();
	void AddModEffect(std::shared_ptr<IModEffect> modEffect);
	std::string modSet;
	std::string parent; // The parent of the mod, there is a limit of one mod equipped per parent
	std::string filePath;

private:
	std::vector<std::shared_ptr<IModEffect>> modEffects;
};