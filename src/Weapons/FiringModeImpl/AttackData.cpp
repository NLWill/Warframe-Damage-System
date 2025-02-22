#include "src/Weapons/FiringModeImpl/AttackData.h"

AttackData::AttackData(DamageData damageData)
{
	this->damageData = damageData;
	subAttacks = {};
}

AttackData::AttackData(DamageData damageData, std::vector<DamageData> subAttacks)
{
	this->damageData = damageData;
	this->subAttacks = subAttacks;
}
