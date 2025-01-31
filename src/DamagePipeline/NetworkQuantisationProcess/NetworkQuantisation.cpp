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
		ServiceLocator::GetLogger().Log(type.ToString());
	}
}
void PrintMap(std::map<DamageType, float> map)
{
	for (std::pair<DamageType, float> type : map)
	{
		string msg = type.first.ToString() + " " + std::to_string(type.second);
		ServiceLocator::GetLogger().Log(msg);
	}
}

void NetworkQuantisation::AddElementsAndQuantise(DamageInstance *damageInstance)
{
	// Parse the elemental bonuses from mods which may affect the final composition of damage types
	auto [elementOrder, elementValues] = ParseElementsFromMods(damageInstance);
	// ServiceLocator::GetLogger().Log("Printing element order");
	// PrintVector(elementOrder);
	// ServiceLocator::GetLogger().Log("Printing element values");
	// PrintMap(elementValues);

	// Iterate over the element queue and combine any pairs of base elements into their combined form
	auto elementsToReplace = CombineMultipleBaseElements(elementOrder, elementValues);
	// ServiceLocator::GetLogger().Log("After combination, the element values are:");
	// PrintMap(elementValues);
	// ServiceLocator::GetLogger().Log("And the elements that must be replaced are:");
	// PrintVector(elementsToReplace);

	// Quantise added elements
	std::map<DamageType, float> quantisedElements = {};
	QuantiseAddedElements(damageInstance, elementValues, quantisedElements);
	// ServiceLocator::GetLogger().Log("After added element quantisation:");
	// PrintMap(quantisedElements);

	// Quantise base elements
	QuantiseBaseElements(damageInstance, quantisedElements);
	// ServiceLocator::GetLogger().Log("After base element quantisation:");
	// PrintMap(quantisedElements);

	// Replace any base elements that have been combined into a combined element (Edge case where innate base element on a weapon)
	for (DamageType combinedDamageType : elementsToReplace)
	{
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
	// ServiceLocator::GetLogger().Log("After quantisation, the elements on the weapon are:");
	// PrintMap(quantisedElements);

	// Set the attack damage data to the new quantised version
	damageInstance->damageData = {};
	for (auto keyValuePair : quantisedElements)
	{
		// As this is the end of the elemental process, replace the non-combining base elements with the normal counterparts
		DamageType damageType = keyValuePair.first;
		switch (damageType)
		{
		case DamageType::DT_HEAT_NON_COMBINING:
			damageType = DamageType::DT_HEAT;
			break;
		case DamageType::DT_COLD_NON_COMBINING:
			damageType = DamageType::DT_COLD;
			break;
		case DamageType::DT_ELECTRICITY_NON_COMBINING:
			damageType = DamageType::DT_ELECTRICITY;
			break;
		case DamageType::DT_TOXIN_NON_COMBINING:
			damageType = DamageType::DT_TOXIN;
			break;
		default:
			break;
		}

		damageInstance->AddDamageValue(DamageValue(damageType, keyValuePair.second));
		/*
		ServiceLocator::GetLogger().Log("After replacement of non-combinings, the elements on the weapon are:");
		for (int i = 0; i < damageInstance->damageData.size(); i++)
		{
			ServiceLocator::GetLogger().Log(damageInstance->damageData[i].damageType.ToString() + " " + std::to_string(damageInstance->damageData[i].value));
		}
		*/
	}
}

std::tuple<std::vector<DamageType>, std::map<DamageType, float>> NetworkQuantisation::ParseElementsFromMods(DamageInstance *damageInstance)
{
	// Go through the mods to identify the added elements
	std::map<DamageType, float> elementValues = {};
	std::vector<DamageType> elementOrder = {};

	auto elementalModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED);

	for (ModEffectBase *modEffect : elementalModEffects)
	{
		DamageType effectDamageType = modEffect->GetDamageType();

		// Filter any incorrect mods that do not have an element
		if (effectDamageType == DamageType::DT_ANY)
		{
			continue;
		}
		
		float effectValue = modEffect->GetModValue(damageInstance);

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

	// For TESTING:
	// elementOrder.push_back(DamageType::DT_COLD);
	// elementValues[DamageType::DT_COLD] = 0.6;
	// elementOrder.push_back(DamageType::DT_ELECTRICITY);
	// elementValues[DamageType::DT_ELECTRICITY] = 0.9;
	// elementOrder.push_back(DamageType::DT_TOXIN);
	// elementValues[DamageType::DT_TOXIN] = 0.9;
	// elementOrder.push_back(DamageType::DT_HEAT);
	// elementValues[DamageType::DT_HEAT] = 0.9;
	// elementOrder.push_back(DamageType::DT_PUNCTURE);
	// elementValues[DamageType::DT_PUNCTURE] += 1.2;

	// Attach the innate elements on the weapon
	for (DamageValue damageValue : damageInstance->weapon->data.attacks.at(damageInstance->attackName).attackData)
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

			float quantisedValue = std::round(physicalElementValue * elementalBonusValues[keyValuePair.first] / quantisationScale) * quantisationScale;

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
