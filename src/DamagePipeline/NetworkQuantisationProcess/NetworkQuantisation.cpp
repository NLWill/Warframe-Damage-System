#include "src/DamagePipeline/NetworkQuantisationProcess/NetworkQuantisation.h"
#include <vector>
#include <string>
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamageValue.h"

void NetworkQuantisation::PerformNetworkQuantisation(FireInstance *fireInstance)
{
	// Get Quantisation scale
	std::vector<DamageValue> baseAttackData;
	try
	{
		baseAttackData = fireInstance->Weapon->data.attacks.at(fireInstance->attackName).attackData;
	}
	catch (std::exception e)
	{
		std::string errorMessage = "Unable to find attack data with name: " + fireInstance->attackName;
		ServiceLocator::GetLogger().LogError(errorMessage);
	}

	float totalBaseDamage = 0;
	for (DamageValue attackElement : baseAttackData){
		totalBaseDamage += attackElement.value;
	}

	float quantisationScale = totalBaseDamage / 16;

	// Quantise added elements


	// Quantise base elements


	// Add all together

}