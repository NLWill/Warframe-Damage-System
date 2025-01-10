#include "src/Mods/ModBase.h"
#include<string>
#include<vector>

class ModFactory{
	public:
	static Mod* GetMod(std::string name);
};