#include "src/Mods/ModBase.h"
#include<string>
#include<vector>

class ModFactory{
	public:
	static std::shared_ptr<Mod> GetMod(std::string name);

	static std::shared_ptr<Mod> GetNullMod();

	private:
	static std::shared_ptr<Mod> CreateMod(std::string databaseData);
	static std::string GetDataFromDatabase(std::string modName);
};