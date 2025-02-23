#pragma once
#include "src/Mods/ModEffects/ConditionalEnum.h"
#include <map>

class ConditionalOverrideManager
{
public:
	ConditionalOverrideManager();
	static ConditionalOverrideManager &Instance();

	void OverrideAll(bool activate);

	bool GetOverride(Conditional condition);
	void SetOverride(Conditional condition, bool isActive);

private:
	static ConditionalOverrideManager *instance;
	bool overrideAll;

	std::map<Conditional, bool> conditionals;
};