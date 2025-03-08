#include "src/Mods/ModOperationType.h"
#include <exception>

std::string ModOperationType::ToString(ModOperationType modOperationType)
{
	for (size_t i = 0; i < modOperationTypeStringNames.size(); i++)
	{
		if (modOperationType == modOperationTypeStringNames[i].first)
		{
			return modOperationTypeStringNames[i].second;
		}
	}
	// Failed to find the entry in the collection
	std::__throw_invalid_argument("Failed to find ModOperationType");
}

ModOperationType ModOperationType::ParseFromString(std::string name)
{
	for (size_t i = 0; i < modOperationTypeStringNames.size(); i++)
	{
		if (name == modOperationTypeStringNames[i].second)
		{
			return modOperationTypeStringNames[i].first;
		}
	}
	// Failed to find string
	std::__throw_invalid_argument("Failed to find string representation of ModOperationType");
}

std::vector<std::pair<ModOperationType, std::string>> ModOperationType::modOperationTypeStringNames{
	{ModOperationType::NONE, "NONE"},
	{ModOperationType::ADD_TO_BASE_VALUE, "ADD_TO_BASE_VALUE"},
	{ModOperationType::STACKING_MULTIPLY, "STACKING_MULTIPLY"},
	{ModOperationType::MULTIPLY, "MULTIPLY"},
	{ModOperationType::ADD, "ADD"},
};