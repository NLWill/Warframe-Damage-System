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
	slotted = false;
	modSet = "";
}

Mod::Mod(std::string name, std::string weaponClass, ModPolarity polarity, int rank, int maxRank, int baseCapacityDrain, std::vector<shared_ptr<ModEffectBase>> &modEffects)
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
	slotted = false;
	modSet = "";
}

Mod::~Mod()
{
}

int Mod::GetCurrentCapacityDrain()
{
	return baseCapacityDrain + rank;
}

std::vector<shared_ptr<ModEffectBase>> Mod::GetModEffects()
{
	return modEffects;
}

void Mod::AddModEffect(shared_ptr<ModEffectBase> modEffect)
{
	modEffects.push_back(modEffect);
}