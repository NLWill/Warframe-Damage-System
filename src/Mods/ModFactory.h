#include "src/Mods/ModBase.h"
#include<string>
#include<vector>

class ModFactory{
	public:
	static shared_ptr<Mod> GetMod(std::string name);

	static shared_ptr<Mod> GetNullMod();

	private:
	static shared_ptr<Mod> CreateMod(std::string databaseData);
	static std::string GetDataFromDatabase(std::string modName);
};