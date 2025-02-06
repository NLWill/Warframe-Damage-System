#include "src/Mods/ModFactory.h"
#include "src/Mods/ModEffects/ConstantModEffect.h"
#include <sqlite3.h>
#include "src/Services/ServiceLocator.h"

Mod *ModFactory::GetMod(std::string name)
{
	Mod *mod = new Mod();
	mod->name = name;
	mod->weaponClass = "Primary";
	mod->polarity = ModPolarity::AP_NONE;
	mod->rank = 10;
	mod->maxRank = 10;
	mod->baseCapacityDrain = 4;

	DamageType modEffectElement = DamageType::ParseDamageTypeName(name);

	std::vector<ModEffectBase> modEffects = {};
	mod->AddModEffect(new ConstantModEffect(modEffectElement, ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED, ModOperationType::STACKING_MULTIPLY, 0.6f));

	return mod;
}

/*
static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char *)data);

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

static Mod *GetModFromDatabase(std::string name)
{
	sqlite3 *modDataBase;
	int exit = 0;
	exit = sqlite3_open("data/Mods/ModData.txt", &modDataBase);

	if (exit)
	{
		std::string errorMessage = sqlite3_errmsg(modDataBase);
		ServiceLocator::GetLogger().LogError("Error open DB " + errorMessage);
		return new Mod();
	}
	else
	{
		ServiceLocator::GetLogger().Log("Opened Database Successfully!");
	}

	std::string data("CALLBACK FUNCTION");
	std::string sqlCommand("SELECT * FROM Mods WHERE Name="+name+";");

	int rc = sqlite3_exec(modDataBase, sqlCommand.c_str(), callback, (void *)data.c_str(), NULL);

	if (rc != SQLITE_OK)
	{
		ServiceLocator::GetLogger().LogError("Error SELECT");
	}
	else
	{
		ServiceLocator::GetLogger().Log("Operation OK!");
	}

	sqlite3_close(modDataBase);

	return new Mod();
}
*/