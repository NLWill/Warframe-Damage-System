#include "src/DamagePipeline/NetworkQuantisationProcess/NetworkQuantisation.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include "src/Services/ServiceLocator.h"
#include "src/DamagePipeline/DamageValue.h"
#include "src/DamagePipeline/DamagePipeline.h"

#define DEBUG_NETWORK_QUANTISATION false

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

void NetworkQuantisation::AddElementsAndQuantise(shared_ptr<DamageInstance> damageInstance)
{
	// Parse the elemental bonuses from mods which may affect the final composition of damage types
	auto [elementOrder, elementValues] = ParseElementsFromMods(damageInstance);
#if DEBUG_NETWORK_QUANTISATION
	ServiceLocator::GetLogger().Log("Printing element order");
	PrintVector(elementOrder);
	ServiceLocator::GetLogger().Log("Printing element values");
	PrintMap(elementValues);
#endif

	// Iterate over the element queue and combine any pairs of base elements into their combined form
	auto elementsToReplace = CombineMultipleBaseElements(elementOrder, elementValues);
#if DEBUG_NETWORK_QUANTISATION
	ServiceLocator::GetLogger().Log("After combination, the element values are:");
	PrintMap(elementValues);
	ServiceLocator::GetLogger().Log("And the elements that must be replaced are:");
	PrintVector(elementsToReplace);
#endif

	// Quantise added elements
	std::map<DamageType, float> quantisedElements = {};
	QuantiseAddedElements(damageInstance, elementValues, quantisedElements);
#if DEBUG_NETWORK_QUANTISATION
	ServiceLocator::GetLogger().Log("After added element quantisation:");
	PrintMap(quantisedElements);
#endif

	// Quantise base elements
	QuantiseBaseElements(damageInstance, quantisedElements);
#if DEBUG_NETWORK_QUANTISATION
	ServiceLocator::GetLogger().Log("After base element quantisation:");
	PrintMap(quantisedElements);
#endif

	// Replace any base elements that have been combined into a combined element (Edge case where innate base element on a weapon)
	for (DamageType combinedDamageType : elementsToReplace)
	{
		auto elementsToBeReplaced = DamageType::DecomposeCombinedElement(combinedDamageType);
		for (size_t i = 0; i < elementsToBeReplaced.size(); i++)
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
#if DEBUG_NETWORK_QUANTISATION
	ServiceLocator::GetLogger().Log("After quantisation, the elements on the weapon are:");
	PrintMap(quantisedElements);
#endif

	// Set the attack damage data to the new quantised version
	damageInstance->damageValues = {};
	for (auto keyValuePair : quantisedElements)
	{
		// As this is the end of the elemental process, replace the non-combining base elements with the normal counterparts
		DamageType damageType = keyValuePair.first;
		switch (damageType)
		{
		case DamageType::DT_FIRE_NON_COMBINING:
			damageType = DamageType::DT_FIRE;
			break;
		case DamageType::DT_FREEZE_NON_COMBINING:
			damageType = DamageType::DT_FREEZE;
			break;
		case DamageType::DT_ELECTRICITY_NON_COMBINING:
			damageType = DamageType::DT_ELECTRICITY;
			break;
		case DamageType::DT_POISON_NON_COMBINING:
			damageType = DamageType::DT_POISON;
			break;
		default:
			break;
		}

		damageInstance->AddDamageValue(DamageValue(damageType, keyValuePair.second));
	}

#if DEBUG_NETWORK_QUANTISATION
	ServiceLocator::GetLogger().Log("After replacement of non-combinings, the elements on the weapon are:");
	for (int i = 0; i < damageInstance->damageValues.size(); i++)
	{
		ServiceLocator::GetLogger().Log(damageInstance->damageValues[i].damageType.ToString() + " " + std::to_string(damageInstance->damageValues[i].value));
	}

	ServiceLocator::GetLogger().Log("The individal element weights are: ");
	PrintMap(damageInstance->GetElementalWeights());
#endif
}

std::tuple<std::vector<DamageType>, std::map<DamageType, float>> NetworkQuantisation::ParseElementsFromMods(shared_ptr<DamageInstance> damageInstance)
{
	// Go through the mods to identify the added elements
	std::map<DamageType, float> elementValues = {};
	std::vector<DamageType> elementOrder = {};

	auto elementalModEffects = damageInstance->GetAllModEffects(ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED);

	for (auto modEffect : elementalModEffects)
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
	// elementOrder.push_back(DamageType::DT_FREEZE);
	// elementValues[DamageType::DT_FREEZE] = 0.6;
	// elementOrder.push_back(DamageType::DT_ELECTRICITY);
	// elementValues[DamageType::DT_ELECTRICITY] = 0.9;
	// elementOrder.push_back(DamageType::DT_POISON);
	// elementValues[DamageType::DT_POISON] = 0.9;
	// elementOrder.push_back(DamageType::DT_FIRE);
	// elementValues[DamageType::DT_FIRE] = 0.9;
	// elementOrder.push_back(DamageType::DT_PUNCTURE);
	// elementValues[DamageType::DT_PUNCTURE] += 1.2;

	// Attach the innate elements on the weapon
	for (auto damageTypePercentage : damageInstance->damageData.percentageDamageDistribution)
	{
		DamageType damageType = damageTypePercentage.first;
		if (std::find(elementOrder.begin(), elementOrder.end(), damageType) != elementOrder.end())
		{
			// The element has already been included from an earlier mod
		}
		else
		{
			// The element has not already been included
			elementOrder.push_back(damageType);
		}

		elementValues[damageType] += 0;
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
		case DamageType::DT_FREEZE:
		case DamageType::DT_ELECTRICITY:
		case DamageType::DT_FIRE:
		case DamageType::DT_POISON:
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

void NetworkQuantisation::QuantiseAddedElements(shared_ptr<DamageInstance> baseAttackData, std::map<DamageType, float> &elementalBonusValues, std::map<DamageType, float> &quantisedElements)
{
	// Calulate the totalBaseDamage of the weapon as well as the quantisation scale
	float totalBaseDamage = baseAttackData->GetTotalDamage();

	for (auto damageTypeModBonusPair : elementalBonusValues)
	{
		float quantisedValue;
		switch (damageTypeModBonusPair.first)
		{
		case DamageType::DT_IMPACT:
		case DamageType::DT_PUNCTURE:
		case DamageType::DT_SLASH:
		{
			// Handle the physical IPS elements separately and only scale off innate values of the same element
			float physicalElementValue = 0;
			for (size_t i = 0; i < baseAttackData->damageValues.size(); i++)
			{
				if (baseAttackData->damageValues[i].damageType == damageTypeModBonusPair.first)
				{
					physicalElementValue = baseAttackData->damageValues[i].value;
					break;
				}
			}

			float quantisedElementWeight = std::round(damageTypeModBonusPair.second * _quantisationResolution * (physicalElementValue / totalBaseDamage)) / _quantisationResolution;
			baseAttackData->GetElementalWeights()[damageTypeModBonusPair.first] += quantisedElementWeight;

			quantisedValue = totalBaseDamage * quantisedElementWeight;

			quantisedElements[damageTypeModBonusPair.first] += quantisedValue;
			break;
		}
		default:
		{
			// Handle the remaining elements together and scale from the total damage
			float quantisedElementWeight = std::round(damageTypeModBonusPair.second * _quantisationResolution) / _quantisationResolution;
			baseAttackData->GetElementalWeights()[damageTypeModBonusPair.first] += quantisedElementWeight;

			quantisedValue = totalBaseDamage * quantisedElementWeight;

			quantisedElements[damageTypeModBonusPair.first] += quantisedValue;
			break;
		}
		}
	}
}

void NetworkQuantisation::QuantiseBaseElements(shared_ptr<DamageInstance> baseAttackData, std::map<DamageType, float> &quantisedElements)
{
	// Calulate the totalBaseDamage of the weapon as well as the quantisation scale
	float totalBaseDamage = baseAttackData->GetTotalDamage();

	// Round each damage type to their nearest quantisation scale point and add it to the total damage of the quantisedElements map
	for (DamageValue damageValue : baseAttackData->damageValues)
	{
		float quantisedElementWeight = std::round(damageValue.value / totalBaseDamage * _quantisationResolution) / _quantisationResolution;
		baseAttackData->GetElementalWeights()[damageValue.damageType] += quantisedElementWeight;

		float quantisedValue = quantisedElementWeight * totalBaseDamage;

		quantisedElements[damageValue.damageType] += quantisedValue;
	}
}
