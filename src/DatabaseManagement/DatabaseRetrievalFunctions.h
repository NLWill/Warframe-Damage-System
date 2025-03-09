#pragma once
#include <string>

class DatabaseRetrievalFunctions
{
public:
	/// @brief Retrieve data from the database pertaining to a named mod
	/// @param modName The name of the desired mod
	/// @return A CSV-style string containing all data required to create a new Mod struct
	static std::string GetModData(std::string modName);

	/// @brief Retrieve data from the database pertaining to a named weapon
	/// @param weaponName The name of the desired weapon
	/// @return A CSV-style string containing all data required to create a new Weapon struct
	static std::string GetWeaponData(std::string weaponName);

	/// @brief Retrieve data from the database pertaining to a named target type
	/// @param targetName The name of the entity to be created
	/// @return A CSV-style string containing all data required to create a new Target struct
	static std::string GetTargetData(std::string targetName);

private:
	enum class SearchType
	{
		Mod,
		Weapon,
		Target
	};

	/// @brief Fetch the file path associated with a given mod name
	/// @param modName The name of the desired Mod
	/// @return A string of the file path needed to get the database data for this mod
	static std::string FindFilePath(std::string name, SearchType searchType);

	/// @brief Fetch the database data for the given Mod name
	/// @param modName The name of the desired Mod
	/// @return Returns a string containing all data inside the provided file
	static std::string GetDataFromDatabase(std::string filePath);
};