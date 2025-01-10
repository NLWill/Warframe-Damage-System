#include "src/Mods/ModBase.h"

Mod::Mod(std::string name, std::string weaponClass, ModPolarity polarity, int rank, int maxRank, int baseCapacityDrain, std::vector<ModEffectBase> &modEffects)
{
	this->name = name;
	this->weaponClass = weaponClass;
	this->polarity = polarity;
	this->rank = rank;
	this->maxRank = maxRank;
	this->baseCapacityDrain = baseCapacityDrain;
	this->modEffects = &modEffects;

	incompatabilityTags = {};
	compatabilityTags = {};
	slotted = false;
	modSet = "";
}

int Mod::getCurrentCapacityDrain()
{
	return baseCapacityDrain + rank;
}
std::vector<ModEffectBase> &Mod::GetModEffects()
{
	return *modEffects;
}