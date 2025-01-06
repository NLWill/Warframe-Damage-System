#include "src/Weapons/DamageType.h"
#include "src/DamagePipeline/DamageInstance.h"

DamageInstance::DamageInstance(const std::vector<DamageValue>& _damageData)
{
	damageData = std::vector<DamageValue>(_damageData);
}