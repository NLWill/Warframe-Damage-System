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
		assert(DamageType::CombineDamageTypes(DamageType::DT_HEAT, DamageType::DT_COLD) == DamageType::DT_BLAST);
		assert(DamageType::CombineDamageTypes(DamageType::DT_HEAT, DamageType::DT_ELECTRICITY) == DamageType::DT_RADIATION);
		assert(DamageType::CombineDamageTypes(DamageType::DT_HEAT, DamageType::DT_TOXIN) == DamageType::DT_GAS);
		assert(DamageType::CombineDamageTypes(DamageType::DT_COLD, DamageType::DT_ELECTRICITY) == DamageType::DT_MAGNETIC);
		assert(DamageType::CombineDamageTypes(DamageType::DT_COLD, DamageType::DT_TOXIN) == DamageType::DT_VIRAL);
		assert(DamageType::CombineDamageTypes(DamageType::DT_ELECTRICITY, DamageType::DT_TOXIN) == DamageType::DT_CORROSIVE);

		// Swap ordering of one
		assert(DamageType::CombineDamageTypes(DamageType::DT_COLD, DamageType::DT_ELECTRICITY) == DamageType::CombineDamageTypes(DamageType::DT_ELECTRICITY, DamageType::DT_COLD));

		// Intentional failure
		try{
			DamageType::CombineDamageTypes(DamageType::DT_BLAST, DamageType::DT_TRUE);
			return EXIT_FAILURE;
		}
		catch (int errorNum){

		}

		// Test decomposition of combined elements
		auto elements = DamageType::DecomposeCombinedElement(DamageType::DT_GAS);
		assert(elements.size() == 2);
		assert((elements[0] == DamageType::DT_HEAT && elements[1] == DamageType::DT_TOXIN) || (elements[1] == DamageType::DT_HEAT || elements[0] == DamageType::DT_TOXIN));
		
		auto elementsFailure = DamageType::DecomposeCombinedElement(DamageType::DT_TAU);
		assert(elementsFailure.size() == 1);
		assert(elementsFailure[0] == DamageType::DT_TAU);
	}
	catch (int errNum){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}