#pragma once
#include <vector>
#include <string>
#include "src/Mods/ModPolarity.h"
#include "src/Mods/ModEffectBase.h"

class Mod
{
public:
	Mod();
	Mod(std::string name,
		std::string weaponClass,
		ModPolarity polarity,
		int rank,
		int maxRank,
		int baseCapacityDrain,
		std::vector<ModEffectBase*> &modEffects
		);
	~Mod();
	std::string name;
	std::vector<std::string> compatabilityTags;
	std::vector<std::string> incompatabilityTags;
	std::string weaponClass;
	ModPolarity polarity;
	bool slotted;
	int rank;
	int maxRank;
	int baseCapacityDrain;
	int getCurrentCapacityDrain();
	std::vector<ModEffectBase*> GetModEffects();
	void AddModEffect(ModEffectBase *modEffect);
	std::string modSet;

	private:
	std::vector<ModEffectBase*> modEffects;
};