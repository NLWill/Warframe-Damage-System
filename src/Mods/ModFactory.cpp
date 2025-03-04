#include "src/Mods/ModFactory.h"
#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/Services/ServiceLocator.h"
#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"

shared_ptr<Mod> ModFactory::GetMod(std::string name)
{
	std::string databaseData = GetDataFromDatabase(name);

	return CreateMod(databaseData);
}

shared_ptr<Mod> ModFactory::CreateMod(std::string databaseData)
{
	// Currently the data should be in the OverallModData form
	auto categoryDataPairs = DatabaseManipulationFunctions::ExtractCategoryDataPairs(databaseData);
	(void)categoryDataPairs;
	return GetNullMod();
}

std::string ModFactory::GetDataFromDatabase(std::string modName)
{
	(void)modName;
	return "";
}

shared_ptr<Mod> ModFactory::GetNullMod()
{
	auto mod = make_shared<Mod>();
	mod->name = "";
	mod->weaponClass = "Primary";
	mod->polarity = ModPolarity::AP_UNIVERSAL;
	mod->rank = 10;
	mod->maxRank = 10;
	mod->baseCapacityDrain = 4;

	return mod;
}