#pragma once
#include<vector>
#include "src/Mods/ModPolarity.h"
#include "src/Mods/ModEffectBase.h"

class Mod{
	public:
	std::string name;
	std::string compatabilityTag;
	std::string weaponClass;
	ModPolarity polarity;
	int rank;
	int maxRank;
	std::vector<ModEffect> modEffects;
};