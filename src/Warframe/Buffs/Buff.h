#pragma once
#include "src/Mods/IModEffect.h"
#include <string>
#include <memory>

class Buff
{
public:
	Buff() = default;
	Buff(std::string name, std::vector<std::shared_ptr<IModEffect>> &modEffects, float duration);
	virtual ~Buff() = default;

	std::vector<std::shared_ptr<IModEffect>> GetAllModEffects();

	std::string GetName();

	bool IsActive();
	float GetRemainingDuration();
	void SetRemainingDuration(float time);

protected:
	std::string name;
	std::vector<std::shared_ptr<IModEffect>> modEffects;
	float remainingDuration;

	// To be moved to separate subclasses
	bool clearAllStacksOnExpire;
	int currentStacks;
	int maxStacks;
	bool isRefreshable;
};