#include "src/Mods/ModBase.h"
#include<string>
#include<vector>

class ModFactory{
	public:
	static Mod* GetMod(std::string name);

	static Mod *GetNullMod();

	private:
	static Mod* CreateMod(std::string databaseData);
};