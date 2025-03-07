#include "src/Mods/ModBase.h"

Mod::Mod()
{
	name = "";
	weaponClass = "";
	polarity = ModPolarity::AP_UNIVERSAL;
	rank = 0;
	maxRank = 0;
	baseCapacityDrain = 0;
	slotType = ModSlotType::MST_NORMAL;
	modEffects = {};

	incompatabilityTags = {};
	compatabilityTags = {};
	parent = "";
	modSet = "";
}

Mod::Mod(std::string name, std::string weaponClass, ModPolarity polarity, int rank, int maxRank, int baseCapacityDrain, std::vector<std::shared_ptr<IModEffect>> &modEffects)
{
	this->name = name;
	this->weaponClass = weaponClass;
	this->polarity = polarity;
	this->rank = rank;
	this->maxRank = maxRank;
	this->baseCapacityDrain = baseCapacityDrain;
	slotType = ModSlotType::MST_NORMAL;
	this->modEffects = modEffects;

	incompatabilityTags = {};
	compatabilityTags = {};
	parent = "";
	modSet = "";
}

Mod::~Mod()
{
}

int Mod::GetCurrentCapacityDrain()
{
	return baseCapacityDrain + rank;
}

std::vector<std::shared_ptr<IModEffect>> Mod::GetModEffects()
{
	return modEffects;
}

void Mod::AddModEffect(std::shared_ptr<IModEffect> modEffect)
{
	modEffects.push_back(modEffect);
}