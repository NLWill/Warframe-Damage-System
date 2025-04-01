#include "src/Mods/ModBase.h"

Mod::Mod()
{
	name = "";
	itemCompatibility = "";
	polarity = ModPolarity::AP_UNIVERSAL;
	rank = 0;
	maxRank = ModFusionLimit::QA_HIGH;
	baseCapacityDrain = ModBaseDrain::QA_LOW;
	disableCapacityDrain = false;
	slotType = ModSlotType::MST_NORMAL;
	modEffects = {};

	incompatabilityTags = {};
	compatabilityTags = {};
	parent = "";
	parents = {};
	modSet = "";
	filePath = "";
}

Mod::Mod(std::string name, std::string itemCompatibility, ModPolarity polarity, int rank, ModFusionLimit maxRank, ModBaseDrain baseCapacityDrain, std::vector<std::shared_ptr<IModEffect>> &modEffects)
{
	this->name = name;
	this->itemCompatibility = itemCompatibility;
	this->polarity = polarity;
	this->rank = rank;
	this->maxRank = maxRank;
	this->baseCapacityDrain = baseCapacityDrain;
	disableCapacityDrain = false;
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
	if (disableCapacityDrain){
		return 0;
	}

	return ModBaseDrain::GetBaseDrainAmount(baseCapacityDrain) + rank;
}

std::vector<std::shared_ptr<IModEffect>> Mod::GetModEffects()
{
	return modEffects;
}

void Mod::EvaluateModEffects(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues)
{
	for (size_t i = 0; i < modEffects.size(); i++)
	{
		modEffects[i]->EvaluateModEffect(damageInstance, upgradeType, modEffectValues);
	}	
}

void Mod::AddModEffect(std::shared_ptr<IModEffect> modEffect)
{
	modEffects.push_back(modEffect);
}