#include "../src/Weapons/DamageType.h"
#include "../src/Services/ServiceLocator.h"

void assert(bool condition){
	if (!condition){
		throw 1;
	}
}

int main(){
	ServiceLocator::Initialise();

	try{
		assert(CombineDamageTypes(DamageType::DT_HEAT, DamageType::DT_COLD) == DamageType::DT_BLAST);
		assert(CombineDamageTypes(DamageType::DT_HEAT, DamageType::DT_ELECTRICITY) == DamageType::DT_RADIATION);
		assert(CombineDamageTypes(DamageType::DT_HEAT, DamageType::DT_TOXIN) == DamageType::DT_GAS);
		assert(CombineDamageTypes(DamageType::DT_COLD, DamageType::DT_ELECTRICITY) == DamageType::DT_MAGNETIC);
		assert(CombineDamageTypes(DamageType::DT_COLD, DamageType::DT_TOXIN) == DamageType::DT_VIRAL);
		assert(CombineDamageTypes(DamageType::DT_ELECTRICITY, DamageType::DT_TOXIN) == DamageType::DT_CORROSIVE);

		// Swap ordering of one
		assert(CombineDamageTypes(DamageType::DT_COLD, DamageType::DT_ELECTRICITY) == CombineDamageTypes(DamageType::DT_ELECTRICITY, DamageType::DT_COLD));

		// Intentional failure
		try{
			CombineDamageTypes(DamageType::DT_BLAST, DamageType::DT_TRUE);
			return EXIT_FAILURE;
		}
		catch (int errorNum){

		}

		// Test decomposition of combined elements
		auto elements = DecomposeCombinedElement(DamageType::DT_GAS);
		assert(elements.size() == 2);
		assert((elements[0] == DamageType::DT_HEAT && elements[1] == DamageType::DT_TOXIN) || (elements[1] == DamageType::DT_HEAT || elements[0] == DamageType::DT_TOXIN));
		
		auto elementsFailure = DecomposeCombinedElement(DamageType::DT_TAU);
		assert(elementsFailure.size() == 1);
		assert(elementsFailure[0] == DamageType::DT_TAU);
	}
	catch (int errNum){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}