#include "src/Weapons/DamageType.h"
#include "src/DamagePipeline/DamageInstance.h"

DamageInstance::DamageInstance(const std::vector<DamageValue> &_damageData)
{
	damageData = std::vector<DamageValue>(_damageData);
}

DamageInstance &DamageInstance::operator*(const float &mult)
{
	return *this *= mult;
}

DamageInstance &DamageInstance::operator=(const DamageInstance &other)
{
	damageData = std::vector<DamageValue>(other.damageData);
	statusEffects = std::vector<StatusEffect>(other.statusEffects);
	critTier = other.critTier;
	return *this;
}

DamageInstance &DamageInstance::operator*=(const float &mult)
{
	for (auto damageValue : this->damageData)
	{
		damageValue = damageValue * mult;
	}

	return *this;
}

float DamageInstance::GetTotalDamage()
{
	float sum = 0;
	for (int i = 0; i < damageData.size(); i++)
	{
		sum += damageData[i].value;
	}
	return sum;
}

void DamageInstance::AddStatusEffect(StatusEffect statusEffect)
{
	if (statusEffect != StatusEffect::PT_NONE)
	{
		statusEffects.push_back(statusEffect);
	}
}
