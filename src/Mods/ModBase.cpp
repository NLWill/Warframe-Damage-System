#include "src/Mods/ModBase.h"

Mod::Mod()
{
	name = "";
	weaponClass = "";
	polarity = ModPolarity::AP_NONE;
	rank = 0;
	maxRank = 0;
	baseCapacityDrain = 0;
	modEffects = {};

	incompatabilityTags = {};
	compatabilityTags = {};
	parent = "";
	slotted = false;
	modSet = "";
}

Mod::Mod(std::string name, std::string weaponClass, ModPolarity polarity, int rank, int maxRank, int baseCapacityDrain, std::vector<ModEffectBase *> &modEffects)
{
	this->name = name;
	this->weaponClass = weaponClass;
	this->polarity = polarity;
	this->rank = rank;
	this->maxRank = maxRank;
	this->baseCapacityDrain = baseCapacityDrain;
	this->modEffects = modEffects;

	incompatabilityTags = {};
	compatabilityTags = {};
	parent = "";
	slotted = false;
	modSet = "";
}

Mod::~Mod()
{
	for (auto effect : modEffects)
	{
		delete effect;
	}
}

int Mod::GetCurrentCapacityDrain()
{
	return baseCapacityDrain + rank;
}

std::vector<ModEffectBase *> Mod::GetModEffects()
{
	return modEffects;
}

void Mod::AddModEffect(ModEffectBase *modEffect)
{
	modEffects.push_back(modEffect);
}