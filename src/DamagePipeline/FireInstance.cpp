#include "src/DamagePipeline/FireInstance.h"
#include "src/Services/ServiceLocator.h"

FireInstance::FireInstance(FireInstance &other) : weapon{other.weapon}
{
	damageInstances = other.damageInstances;
}

FireInstance::FireInstance(shared_ptr<Weapon> _weapon, std::string _attackName) : weapon{_weapon}
{
	attackName = _attackName;
}

FireInstance::~FireInstance()
{
}

float FireInstance::GetTotalDamage()
{
	float sum = 0;
	for (size_t i = 0; i < damageInstances.size(); i++)
	{
		sum += damageInstances[i]->GetTotalDamage();
	}
	return sum;
}