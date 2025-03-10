#pragma once
#include "src/Mods/ModBase.h"
#include <string>
#include <vector>

class ModFactory
{
public:
	/// @brief Load the Mod with the corresponding name from the database and create a new Mod instance with all relevant ModEffects
	/// @param name The name of the desired Mod
	/// @return A shared pointer to the Mod struct
	static std::shared_ptr<Mod> GetMod(std::string name);

	/// @brief Create an empty Mod struct which has no mod effects
	/// @return A shared pointer to an empty Mod struct
	static std::shared_ptr<Mod> GetNullMod();

private:
	/// @brief Create the Mod struct by parsing appropriate data from the database
	/// @param databaseData The data from the database
	/// @return A shared pointer to the Mod struct
	static std::shared_ptr<Mod> CreateMod(std::string databaseData);

	// An enum of all the Mod categories handled by this ModFactory
	enum class DatabaseCategoryCode
	{
		ignoreEntry,
		// Overall Mod Data struct categories
		data,
		id,
		name,
		parent,
		parents,
		path,
		// Mod Data struct categories
		compatabilityTags,
		incompatabilityTags,
		itemCompatibility,
		polarity,
		slotType,
		fusionLimit,
		baseCapacityDrain,
		disableCapacityDrain,
		modSet,
		upgrades,
		// Mod effect categories
		upgradeType,
		operationType,
		value,
		damageType,
		factionType,

	};

	// Convert string representations of data categories into enum form to enable switch expressions etc.
	// The format of the string in this function must exactly match how it appears in the database file.
	static DatabaseCategoryCode HashString(std::string &category);

	/// @brief Process the category entries supplied in the OverallModData struct (as described in /data/Mods/Mod Data Structure.txt)
	/// @param mod A shared pointer to the empty Mod struct that is going to be populated
	/// @param databaseData The database data required to fill the data in the Mod
	static void ProcessOverallModDataStruct(std::shared_ptr<Mod> mod, std::string databaseData);

	/// @brief Process the category entries associated with the ModData struct (as described in /data/Mods/Mod Data Structure.txt)
	/// @param mod A shared pointer to the Mod struct that is being populated
	/// @param categoryDataPairs A vector of pairs of strings containing the category label and associated data
	static void ProcessDataStruct(std::shared_ptr<Mod> mod, std::vector<std::pair<std::string, std::string>> categoryDataPairs);

	/// @brief Process the category entries associated with the creation of a new ModEffect
	/// @param categoryDataPairs A vector of pairs of strings containing the category label and associated data
	/// @return Returns a shared pointer to a new IModEffect created from the data
	static std::shared_ptr<IModEffect> ProcessModEffectData(std::vector<std::pair<std::string, std::string>> categoryDataPairs);
};