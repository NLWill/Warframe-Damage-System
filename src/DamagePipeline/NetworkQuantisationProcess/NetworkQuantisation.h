#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include <vector>
#include "src/Weapons/DamageType.h"

class NetworkQuantisation
{
public:
	static void AddElementsAndQuantise(DamageInstance *damageInstance);

private:
	static std::tuple<std::vector<DamageType>, std::map<DamageType, float>> ParseElementsFromMods(DamageInstance *damageInstance);

	static std::vector<DamageType> CombineMultipleBaseElements(std::vector<DamageType> &elementOrder, std::map<DamageType, float> &elementBonusValues);

	static void QuantiseAddedElements(DamageInstance *baseAttackData, std::map<DamageType, float> &elementalBonusValues, std::map<DamageType, float> &quantisedElements);

	static void QuantiseBaseElements(DamageInstance *baseAttackData, std::map<DamageType, float> &quantisedElements);

	static constexpr float _quantisationResolution = 16;
};