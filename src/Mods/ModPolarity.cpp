#include "src/Mods/ModPolarity.h"
#include <exception>

std::string ModPolarity::ToString(ModPolarity modPolarity)
{
	for (size_t i = 0; i < modPolarityStringNames.size(); i++)
	{
		if (modPolarity == modPolarityStringNames[i].first)
		{
			return modPolarityStringNames[i].second;
		}
	}
	// Failed to find the entry in the collection
	std::__throw_invalid_argument("Failed to find ModPolarity");
}

ModPolarity ModPolarity::ParseFromString(std::string name)
{
	for (size_t i = 0; i < modPolarityStringNames.size(); i++)
	{
		if (name == modPolarityStringNames[i].second)
		{
			return modPolarityStringNames[i].first;
		}
	}
	// Failed to find string
	std::__throw_invalid_argument("Failed to parse string representation of ModPolarity");
}

std::vector<std::pair<ModPolarity, std::string>> ModPolarity::modPolarityStringNames{
	{ModPolarity::AP_UNIVERSAL, "AP_UNIVERSAL"},
	{ModPolarity::AP_ATTACK, "AP_ATTACK"},
	{ModPolarity::AP_DEFENSE, "AP_DEFENSE"},
	{ModPolarity::AP_WARD, "AP_WARD"},
	{ModPolarity::AP_TACTIC, "AP_TACTIC"},
	{ModPolarity::AP_POWER, "AP_POWER"},
	{ModPolarity::AP_PRECEPT, "AP_PRECEPT"},
	{ModPolarity::AP_UMBRA, "AP_UMBRA"},
	{ModPolarity::AP_FUSION, "AP_FUSION"},
	{ModPolarity::AP_ANY, "AP_ANY"},
};
