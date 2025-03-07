#pragma once
#include <vector>
#include "src/Weapons/FiringModeImpl/DamageData.h"

struct AttackData{
	public:
	AttackData() = default;
	AttackData(DamageData damageData);
	AttackData(DamageData damageData, std::vector<DamageData> subAttacks);
	
	DamageData damageData;
	std::vector<DamageData> subAttacks;
};