#pragma once
#include "src/Mods/ModEffectBase.h"
#include <string>

class Buff
{
public:
	Buff() = default;
	Buff(std::string name, std::vector<ModEffectBase *> &modEffects, float duration);
	virtual ~Buff()
	{
		while (!modEffects.empty())
		{
			delete modEffects.back();
			modEffects.pop_back();
		}
	}

	std::vector<ModEffectBase *> GetAllModEffects();

	std::string GetName();

	bool IsActive();
	float GetRemainingDuration();
	void SetRemainingDuration(float time);

protected:
	std::string name;
	std::vector<ModEffectBase *> modEffects;
	float remainingDuration;

	// To be moved to separate subclasses
	bool clearAllStacksOnExpire;
	int currentStacks;
	int maxStacks;
	bool isRefreshable;
};