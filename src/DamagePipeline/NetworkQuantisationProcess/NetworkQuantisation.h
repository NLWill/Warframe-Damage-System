#pragma once
#include "src/DamagePipeline/FireInstance.h"
#include <vector>
#include "src/Weapons/DamageType.h"

class NetworkQuantisation
{
public:
	static void AddElementsAndQuantise(FireInstance *fireInstance);

private:
	static std::tuple<std::vector<DamageType>, std::map<DamageType, float>> ParseElementsFromMods(FireInstance *fireInstance);

	static std::vector<DamageType> CombineMultipleBaseElements(std::vector<DamageType> &elementOrder, std::map<DamageType, float> &elementBonusValues);

	static void QuantiseAddedElements(std::vector<DamageValue> &baseAttackData, std::map<DamageType, float> &elementalBonusValues, std::map<DamageType, float> &quantisedElements);

	static void QuantiseBaseElements(std::vector<DamageValue> &baseAttackData, std::map<DamageType, float> &quantisedElements);

	static constexpr float _quantisationResolution = 16;
};