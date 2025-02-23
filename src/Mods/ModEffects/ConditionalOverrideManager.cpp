#include "src/Mods/ModEffects/ConditionalOverrideManager.h"

ConditionalOverrideManager::ConditionalOverrideManager()
{
}

ConditionalOverrideManager &ConditionalOverrideManager::Instance()
{
	if (instance == nullptr)
	{
		//std::cout << "Creating new ConditionalOverrideManager instance" << std::endl;
		instance = new ConditionalOverrideManager();
	}

	return *instance;
}

void ConditionalOverrideManager::OverrideAll(bool activate)
{
	overrideAll = activate;
}

bool ConditionalOverrideManager::GetOverride(Conditional condition)
{
	if (overrideAll)
	{
		return true;
	}

	if (conditionals.count(condition) == 0)
	{
		//std::cout << "Key was not found in override map during read process, inserting it" << std::endl;
		conditionals.insert({condition, false});
	}

	return conditionals[condition];
}

void ConditionalOverrideManager::SetOverride(Conditional condition, bool isActive)
{
	if (conditionals.count(condition) == 0)
	{
		//std::cout << "Key was not found in override map during set process, inserting it" << std::endl;
		conditionals.insert({condition, isActive});
	}

	conditionals[condition] = isActive;
}

ConditionalOverrideManager *ConditionalOverrideManager::instance;
