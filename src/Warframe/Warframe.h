#pragma once
#include "src/Warframe/Buffs/Buff.h"
#include <vector>

class Warframe{
	public:
	Warframe();
	std::vector<Buff> activeBuffs;
};