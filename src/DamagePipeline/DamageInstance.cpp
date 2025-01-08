#include "src/Weapons/DamageType.h"
#include "src/DamagePipeline/DamageInstance.h"
#include "DamageInstance.h"

DamageInstance::DamageInstance(const std::vector<DamageValue>& _damageData)
{
	damageData = std::vector<DamageValue>(_damageData);
}

DamageInstance& DamageInstance::operator*(const float &mult)
{
	return *this *= mult;
}

DamageInstance& DamageInstance::operator=(const DamageInstance& other){
	damageData = std::vector<DamageValue>(other.damageData);
	statusEffects = std::vector<StatusEffect>(other.statusEffects);
	critTier = other.critTier;
}

DamageInstance& DamageInstance::operator*=(const float &mult)
{
	for (auto damageValue : this->damageData){
		damageValue = damageValue * mult;
	}

	return *this;
}
