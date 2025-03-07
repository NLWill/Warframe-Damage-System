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
	/// @brief Name of the mod
	std::string name;
	/// @brief Unique id number of the mod
	int id;
	/// @brief List of features that a weapon must fulfil to be allowed to equip the mod
	std::vector<std::string> compatabilityTags;
	/// @brief List of tags that invalidate a weapon from equipping a mod e.g. CRPBOW for Lenz
	std::vector<std::string> incompatabilityTags;
	/// @brief The group of weapons that this mod is intended for e.g. rifles or shotguns
	std::string weaponClass;
	/// @brief The polarity of the mod
	ModPolarity polarity;
	/// @brief The slot type that this mod occupies. E.g. Normal/Aura/Exilus/Arcane etc.
	ModSlotType slotType;
	/// @brief The upgrade tier of the mod
	int rank;
	/// @brief The maximum upgrade tier of the mod
	int maxRank;
	/// @brief The capacity drain of the mod at rank 0
	int baseCapacityDrain;
	/// @brief Get the capacity drain of this mod
	/// @return
	int GetCurrentCapacityDrain();
	/// @brief Get all the effects that this mod contains
	/// @return A vector of shared pointers to IModEffects
	std::vector<std::shared_ptr<IModEffect>> GetModEffects();
	/// @brief Add a new mod effect to the mod
	/// @param modEffect A shared pointer to the new mod effect
	void AddModEffect(std::shared_ptr<IModEffect> modEffect);
	/// @brief Designates whether this mod belongs to a collective set. Empty string denotes no set
	std::string modSet;
	/// @brief The parent of the mod, there is a limit of one mod equipped per parent
	std::string parent;
	/// @brief The file path to find the original mod's data
	std::string filePath;

private:
	/// @brief A list of mod effects that this Mod contains
	std::vector<std::shared_ptr<IModEffect>> modEffects;
};