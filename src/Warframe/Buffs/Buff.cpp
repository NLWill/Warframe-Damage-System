#include "src/Warframe/Buffs/Buff.h"
#include "Buff.h"

Buff::Buff(std::string name, std::vector<std::shared_ptr<IModEffect>> &modEffects, float duration)
{
	this->name = name;
	this->modEffects = modEffects;
	remainingDuration = duration;
}

std::vector<std::shared_ptr<IModEffect>> Buff::GetAllModEffects()
{
	return modEffects;
}

std::string Buff::GetName()
{
	return name;
}

bool Buff::IsActive()
{
	return remainingDuration > 0;
}

float Buff::GetRemainingDuration()
{
	return remainingDuration;
}

void Buff::SetRemainingDuration(float time)
{
	remainingDuration = time;
}
