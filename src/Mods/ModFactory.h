#include "src/Mods/ModBase.h"
#include<string>
#include<vector>

class ModFactory{
	public:
	/// @brief Load the Mod with the corresponding name from the database and create a new Mod instance with all relevant ModEffects
	/// @param name The name of the desired Mod
	/// @return A shared pointer to the Mod struct
	static std::shared_ptr<Mod> GetMod(std::string name);

	/// @brief Create an empty Mod struct which has no mod effects
	/// @return A shared pointer to the empty Mod struct
	static std::shared_ptr<Mod> GetNullMod();

	private:
	/// @brief Fetch the database data for the given Mod name
	/// @param modName The name of the desired Mod
	/// @return A CSV database string containing all data required to create the Mod
	static std::string GetDataFromDatabase(std::string modName);

	/// @brief Create the Mod struct by parsing appropriate data from the database
	/// @param databaseData The data from the database
	/// @return A shared pointer to the Mod struct
	static std::shared_ptr<Mod> CreateMod(std::string databaseData);
};