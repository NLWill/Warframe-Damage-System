#include "src/Mods/ModFactory.h"
#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/Services/ServiceLocator.h"
#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"

Mod *ModFactory::GetMod(std::string name)
{
	std::string databaseData;

	return CreateMod(databaseData);
}

Mod *ModFactory::CreateMod(std::string databaseData)
{
	// Currently the data should be in the OverallModData form
	auto categoryDataPairs = DatabaseManipulationFunctions::ExtractCategoryDataPairs(databaseData);
	return nullptr;
}

Mod *ModFactory::GetNullMod()
{
	Mod *mod = new Mod();
	mod->name = "";
	mod->weaponClass = "Primary";
	mod->polarity = ModPolarity::AP_UNIVERSAL;
	mod->rank = 10;
	mod->maxRank = 10;
	mod->baseCapacityDrain = 4;

	std::vector<ModEffectBase> modEffects = {};

	return mod;
}