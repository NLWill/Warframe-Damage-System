#include "../src/Mods/ModOperationType.h"
#include "../src/Mods/ModUpgradeType.h"
#include "../src/Mods/ModPolarity.h"
#include "../src/Mods/ModSlotType.h"
#include <string>

void assert(bool condition){
	if (!condition){
		throw 1;
	}
}

int main(){
	try
	{
		// Test ModOperationType
		assert(ModOperationType::ToString(ModOperationType::ADD_TO_BASE_VALUE) == "ADD_TO_BASE_VALUE");
		assert(ModOperationType::ParseFromString("STACKING_MULTIPLY") == ModOperationType::STACKING_MULTIPLY);

		// Test ModUpgradeType
		assert(ModUpgradeType::ToString(ModUpgradeType::WEAPON_CRIT_CHANCE) == "WEAPON_CRIT_CHANCE");
		assert(ModUpgradeType::ParseFromString("WEAPON_FIRE_ITERATIONS") == ModUpgradeType::WEAPON_FIRE_ITERATIONS);
		
		// Intentional failure
		try
		{
			auto result = ModUpgradeType::ParseFromString("asofmaosfma");
			assert(result != ModUpgradeType::NO_EFFECT);
			return EXIT_FAILURE;
		}
		catch (...)
		{
		}

		// Test ModPolarity
		assert(ModPolarity::ToString(ModPolarity::AP_PRECEPT) == "AP_PRECEPT");
		assert(ModPolarity::ParseFromString("AP_ATTACK") == ModPolarity::AP_ATTACK);

		// Test ModSlotType
		ModSlotType arcaneSlotType = ModSlotType::MST_ARCANE;
		assert(arcaneSlotType.ToString() == "MST_ARCANE");
		assert(ModSlotType::ParseFromString("MST_NORMAL") == ModSlotType::MST_NORMAL);
	}
	catch (...)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}