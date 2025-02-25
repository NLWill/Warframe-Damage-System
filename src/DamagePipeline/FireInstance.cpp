#include "src/DamagePipeline/FireInstance.h"
#include "src/Services/ServiceLocator.h"
#include "FireInstance.h"

FireInstance::FireInstance(FireInstance &other)
{
	damageInstances = other.damageInstances;
}

FireInstance::FireInstance(Weapon &_weapon, std::string _attackName)
{
	weapon = &_weapon;
	attackName = _attackName;
}

FireInstance::~FireInstance()
{
	weapon = nullptr;
	for (auto pointer : damageInstances){
		delete pointer;
	}
	damageInstances.clear();
}

float FireInstance::GetTotalDamage()
{
	float sum = 0;
	for (int i = 0; i < damageInstances.size(); i++)
	{
		sum += damageInstances[i]->GetTotalDamage();
	}
	return sum;
}