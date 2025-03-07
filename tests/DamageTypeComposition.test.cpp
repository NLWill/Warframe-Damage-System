#include "../src/Weapons/DamageType.h"
#include "../src/Services/ServiceLocator.h"
#include "../src/Services/Logging/LogService.h"

void assert(bool condition)
{
	if (!condition)
	{
		throw 1;
	}
}

int main()
{
	auto logSystem = std::make_shared<LogService>();
	ServiceLocator::RegisterService<ILogService>(logSystem);
	try
	{
		assert(DamageType::CombineDamageTypes(DamageType::DT_FIRE, DamageType::DT_FREEZE) == DamageType::DT_EXPLOSION);
		assert(DamageType::CombineDamageTypes(DamageType::DT_FIRE, DamageType::DT_ELECTRICITY) == DamageType::DT_RADIATION);
		assert(DamageType::CombineDamageTypes(DamageType::DT_FIRE, DamageType::DT_POISON) == DamageType::DT_GAS);
		assert(DamageType::CombineDamageTypes(DamageType::DT_FREEZE, DamageType::DT_ELECTRICITY) == DamageType::DT_MAGNETIC);
		assert(DamageType::CombineDamageTypes(DamageType::DT_FREEZE, DamageType::DT_POISON) == DamageType::DT_VIRAL);
		assert(DamageType::CombineDamageTypes(DamageType::DT_ELECTRICITY, DamageType::DT_POISON) == DamageType::DT_CORROSIVE);

		// Swap ordering of one
		assert(DamageType::CombineDamageTypes(DamageType::DT_FREEZE, DamageType::DT_ELECTRICITY) == DamageType::CombineDamageTypes(DamageType::DT_ELECTRICITY, DamageType::DT_FREEZE));

		// Intentional failure
		try
		{
			DamageType::CombineDamageTypes(DamageType::DT_EXPLOSION, DamageType::DT_TRUE);
			return EXIT_FAILURE;
		}
		catch (int errorNum)
		{
		}

		// Test decomposition of combined elements
		auto elements = DamageType::DecomposeCombinedElement(DamageType::DT_GAS);
		assert(elements.size() == 2);
		assert((elements[0] == DamageType::DT_FIRE && elements[1] == DamageType::DT_POISON) || (elements[1] == DamageType::DT_FIRE || elements[0] == DamageType::DT_POISON));

		auto elementsFailure = DamageType::DecomposeCombinedElement(DamageType::DT_TAU);
		assert(elementsFailure.size() == 1);
		assert(elementsFailure[0] == DamageType::DT_TAU);
	}
	catch (int errNum)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}