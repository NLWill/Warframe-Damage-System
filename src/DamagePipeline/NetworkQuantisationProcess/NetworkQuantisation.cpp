#include "src/DamagePipeline/NetworkQuantisationProcess/NetworkQuantisation.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamageValue.h"
#include "src/DamagePipeline/DamagePipeline.h"

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
	// Parse the elemental bonuses from mods which may affect the final composition of damage types
	auto [elementOrder, elementValues] = ParseElementsFromMods(fireInstance);
	ServiceLocator::GetLogger().Log("Printing element order");
	PrintVector(elementOrder);
	ServiceLocator::GetLogger().Log("Printing element values");
	PrintMap(elementValues);

	// Iterate over the element queue and combine any pairs of base elements into their combined form
	auto elementsToReplace = CombineMultipleBaseElements(elementOrder, elementValues);
	ServiceLocator::GetLogger().Log("After combination, the element values are:");
	PrintMap(elementValues);
	ServiceLocator::GetLogger().Log("And the elements that must be replaced are:");
	PrintVector(elementsToReplace);

	for (DamageInstance *damageInstance : fireInstance->damageInstances)
	{
		// Quantise added elements
		std::map<DamageType, float> quantisedElements = {};
		QuantiseAddedElements(damageInstance, elementValues, quantisedElements);

		// Quantise base elements
		QuantiseBaseElements(damageInstance, quantisedElements);

		// Replace any base elements that have been combined into a combined element (Edge case where innate base element on a weapon)
		for (DamageType combinedDamageType : elementsToReplace){
			auto elementsToBeReplaced = DamageType::DecomposeCombinedElement(combinedDamageType);
			for (int i = 0; i < elementsToBeReplaced.size(); i++)
			{
				quantisedElements[combinedDamageType] += quantisedElements[elementsToBeReplaced[i]];
				quantisedElements[elementsToBeReplaced[i]] = 0;
			}			
		}

		// Remove any 0-value elements
		for (auto it = quantisedElements.cbegin(); it != quantisedElements.cend(); /* no increment */)
		{
			if (it->second <= 0)
			{
				it = quantisedElements.erase(it);
			}
			else
			{
				++it;
			}
		}
		ServiceLocator::GetLogger().Log("After quantisation, the elements on the weapon are:");
		PrintMap(quantisedElements);
		
		// Set the attack damage data to the new quantised version
		damageInstance->damageData = {};
		for (auto keyValuePair : quantisedElements)
		{
			damageInstance->AddDamageValue(DamageValue(keyValuePair.first, keyValuePair.second));
		}
		
	}
}

std::tuple<std::vector<DamageType>, std::map<DamageType, float>> NetworkQuantisation::ParseElementsFromMods(FireInstance *fireInstance)
{
	// Go through the mods to identify the added elements
	std::map<DamageType, float> elementValues = {};
	std::vector<DamageType> elementOrder = {};

	auto elementalModEffects = fireInstance->GetAllModEffects(ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED);

	for (ModEffectBase *modEffect : elementalModEffects)
	{
		DamageType effectDamageType = modEffect->GetDamageType();
		float effectValue = modEffect->GetModValue();

		// Filter any incorrect mods that do not have an element
		if (effectDamageType == DamageType::DT_ANY)
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

	// Attach the innate elements on the weapon
	for (DamageValue damageValue : fireInstance->weapon->data.attacks.at(fireInstance->attackName).attackData)
	{
		if (std::find(elementOrder.begin(), elementOrder.end(), damageValue.damageType) != elementOrder.end())
		{
			// The element has already been included from an earlier mod
		}
		else
		{
			// The element has not already been included
			elementOrder.push_back(damageValue.damageType);
		}

		elementValues[damageValue.damageType] += 0;
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
		case DamageType::DT_COLD:
		case DamageType::DT_ELECTRICITY:
		case DamageType::DT_HEAT:
		case DamageType::DT_TOXIN:
			if (baseElementTracker.size() == 0)
			{
				baseElementTracker.push(damageType);
			}
			else
			{
				DamageType otherDamageTypeToCombine = baseElementTracker.top();
				baseElementTracker.pop();

				// Identify what element to replace the two combining base elements
				DamageType combinedElement = DamageType::CombineDamageTypes(damageType, otherDamageTypeToCombine);

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

void NetworkQuantisation::QuantiseAddedElements(DamageInstance *baseAttackData, std::map<DamageType, float> &elementalBonusValues, std::map<DamageType, float> &quantisedElements)
{
	// Calulate the totalBaseDamage of the weapon as well as the quantisation scale
	float totalBaseDamage = baseAttackData->GetTotalDamage();

	float quantisationScale = totalBaseDamage / _quantisationResolution;

	for (auto keyValuePair : elementalBonusValues)
	{
		float quantisedValue;
		switch (keyValuePair.first)
		{
		case DamageType::DT_IMPACT:
		case DamageType::DT_PUNCTURE:
		case DamageType::DT_SLASH:
		{
			// Handle the physical IPS elements separately and only scale off innate values of the same element
			float physicalElementValue = 0;
			for (int i = 0; i < baseAttackData->damageData.size(); i++)
			{
				if (baseAttackData->damageData[i].damageType == keyValuePair.first)
				{
					physicalElementValue = baseAttackData->damageData[i].value;
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

void NetworkQuantisation::QuantiseBaseElements(DamageInstance *baseAttackData, std::map<DamageType, float> &quantisedElements)
{
	// Calulate the totalBaseDamage of the weapon as well as the quantisation scale
	float totalBaseDamage = baseAttackData->GetTotalDamage();

	float quantisationScale = totalBaseDamage / _quantisationResolution;

	// Round each damage type to their nearest quantisation scale point and add it to the total damage of the quantisedElements map
	for (DamageValue damageValue : baseAttackData->damageData)
	{
		float quantisedValue = std::round(damageValue.value / quantisationScale) * quantisationScale;

		quantisedElements[damageValue.damageType] += quantisedValue;
	}
}
