#include "src/DamagePipeline/NetworkQuantisationProcess/NetworkQuantisation.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamageValue.h"

void PrintVector(std::vector<DamageType> vec)
{
	for (DamageType type : vec)
	{
		ServiceLocator::GetLogger().Log(std::to_string(type));
	}
}
void PrintMap(std::map<DamageType, float> map)
{
	for (auto type : map)
	{
		string msg = std::to_string(type.first) + " " + std::to_string(type.second);
		ServiceLocator::GetLogger().Log(msg);
	}
}

void NetworkQuantisation::AddElementsAndQuantise(FireInstance *fireInstance)
{
	// Get Quantisation scale
	std::vector<DamageValue> baseAttackData;
	try
	{
		baseAttackData = fireInstance->weapon->data.attacks.at(fireInstance->attackName).attackData;
	}
	catch (std::exception e)
	{
		std::string errorMessage = "Unable to find attack data with name: " + fireInstance->attackName;
		ServiceLocator::GetLogger().LogError(errorMessage);
	}

	// Parse the elemental bonuses from mods which may affect the final composition of damage types
	auto [elementOrder, elementValues] = ParseElementsFromMods(fireInstance);
	ServiceLocator::GetLogger().Log("Printing element order");
	PrintVector(elementOrder);
	ServiceLocator::GetLogger().Log("Printing element values");
	PrintMap(elementValues);

	auto elementsToReplace = CombineMultipleBaseElements(elementOrder, elementValues);
	ServiceLocator::GetLogger().Log("After combination, the element values are:");
	PrintMap(elementValues);
	ServiceLocator::GetLogger().Log("And the elements that must be replaced are:");
	PrintVector(elementsToReplace);

	// Quantise added elements
	std::map<DamageType, float> quantisedElements = {};
	QuantiseAddedElements(baseAttackData, elementValues, quantisedElements);

	// Quantise base elements
	QuantiseBaseElements(baseAttackData, quantisedElements);

	// Add all together and remove any 0-value elements
	ServiceLocator::GetLogger().Log("After quantisation, the elements on the weapon are:");
	PrintMap(quantisedElements);
}

std::tuple<std::vector<DamageType>, std::map<DamageType, float>> NetworkQuantisation::ParseElementsFromMods(FireInstance *fireInstance)
{
	// Go through the mods to identify the added elements
	std::map<DamageType, float> elementValues = {};
	std::vector<DamageType> elementOrder = {};
	for (Mod *mod : fireInstance->weapon->equippedMods)
	{
		for (int i = 0; i < mod->GetModEffects().size(); i++)
		{
			DamageType effectDamageType = mod->GetModEffects()[i]->GetDamageType();
			float effectValue = mod->GetModEffects()[i]->GetModValue();

			if (effectDamageType == DT_ANY || mod->GetModEffects()[i]->GetUpgradeType() != ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED)
			{
				continue;
			}

			if (std::find(elementOrder.begin(), elementOrder.end(), effectDamageType) != elementOrder.end())
			{
				// The element has already been included from an earlier mod
			}
			else
			{
				// The element has not already been included
				elementOrder.push_back(effectDamageType);
			}

			elementValues[effectDamageType] += effectValue;
		}
	}

	// Attach the innate elements on the weapon
	for (DamageValue damageValue : fireInstance->weapon->data.attacks.at(fireInstance->attackName).attackData)
	{
		if (std::find(elementOrder.begin(), elementOrder.end(), damageValue.type) != elementOrder.end())
		{
			// The element has already been included from an earlier mod
		}
		else
		{
			// The element has not already been included
			elementOrder.push_back(damageValue.type);
		}

		elementValues[damageValue.type] += 0;
	}

	return {elementOrder, elementValues};
}

std::vector<DamageType> NetworkQuantisation::CombineMultipleBaseElements(std::vector<DamageType> &elementOrder, std::map<DamageType, float> &elementModValues)
{
	// Flow through the elements list and generate the combined elements if there are more than one base elements
	std::stack<DamageType> baseElementTracker = {};
	std::vector<DamageType> baseElementsToReplace = {};
	for (auto damageType : elementOrder)
	{
		switch (damageType)
		{
		case DT_COLD:
		case DT_ELECTRICITY:
		case DT_HEAT:
		case DT_TOXIN:
			if (baseElementTracker.size() == 0)
			{
				baseElementTracker.push(damageType);
			}
			else
			{
				DamageType otherDamageTypeToCombine = baseElementTracker.top();
				baseElementTracker.pop();

				// Identify what element to replace the two combining base elements
				DamageType combinedElement = CombineDamageTypes(damageType, otherDamageTypeToCombine);

				// Add their percentage bonuses to the combined element
				elementModValues[combinedElement] += elementModValues[damageType];
				elementModValues[combinedElement] += elementModValues[otherDamageTypeToCombine];

				// Set their individual bonuses to 0
				elementModValues[damageType] = 0;
				elementModValues[otherDamageTypeToCombine] = 0;

				baseElementsToReplace.push_back(combinedElement);
			}
			break;
		default:
			break;
		}
	}

	return baseElementsToReplace;
}

void NetworkQuantisation::QuantiseAddedElements(std::vector<DamageValue> &baseAttackData, std::map<DamageType, float> &elementalBonusValues, std::map<DamageType, float> &quantisedElements)
{
	// Calulate the totalBaseDamage of the weapon as well as the quantisation scale
	float totalBaseDamage = 0;
	for (DamageValue attackElement : baseAttackData)
	{
		totalBaseDamage += attackElement.value;
	}

	float quantisationScale = totalBaseDamage / _quantisationResolution;

	for (auto keyValuePair : elementalBonusValues)
	{
		float quantisedValue;
		switch (keyValuePair.first)
		{
		case DT_IMPACT:
		case DT_PUNCTURE:
		case DT_SLASH:
		{
			// Handle the physical IPS elements separately and only scale off innate values of the same element
			float physicalElementValue = 0;
			for (int i = 0; i < baseAttackData.size(); i++)
			{
				if (baseAttackData[i].type == keyValuePair.first)
				{
					physicalElementValue = baseAttackData[i].value;
					break;
				}
			}

			float quantisedValue = std::round(physicalElementValue / quantisationScale) * quantisationScale;

			quantisedElements[keyValuePair.first] += quantisedValue;
			break;
		}
		default:
		{
			// Handle the remaining elements together and scale from the total damage
			float quantisedValue = std::round(keyValuePair.second * totalBaseDamage / quantisationScale) * quantisationScale;

			quantisedElements[keyValuePair.first] += quantisedValue;
			break;
		}
		}
	}
}

void NetworkQuantisation::QuantiseBaseElements(std::vector<DamageValue> &baseAttackData, std::map<DamageType, float> &quantisedElements)
{
	// Calulate the totalBaseDamage of the weapon as well as the quantisation scale
	float totalBaseDamage = 0;
	for (DamageValue attackElement : baseAttackData)
	{
		totalBaseDamage += attackElement.value;
	}

	float quantisationScale = totalBaseDamage / _quantisationResolution;

	// Round each damage type to their nearest quantisation scale point and add it to the total damage of the quantisedElements map
	for (DamageValue damageValue : baseAttackData)
	{
		float quantisedValue = std::round(damageValue.value / quantisationScale) * quantisationScale;

		quantisedElements[damageValue.type] += quantisedValue;
	}
}
