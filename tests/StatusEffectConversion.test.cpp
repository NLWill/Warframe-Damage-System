#include "../src/Weapons/StatusEffect.h"
#include "../src/Services/ServiceLocator.h"

void assert(bool condition){
	if (!condition){
		throw 1;
	}
}

int main(){
	ServiceLocator::Initialise();

	try{
		assert(GetStatusEffectFromElement(DT_BLAST) == StatusEffect::PT_FLASHBANG);
		assert(GetStatusEffectFromElement(DT_HEAT) == StatusEffect::PT_IMMOLATION);
		assert(GetStatusEffectFromElement(DT_VOID) == StatusEffect::PT_VOID);
		assert(GetStatusEffectFromElement(DT_CORROSIVE) == StatusEffect::PT_CAUSTIC_BURN);
		assert(GetStatusEffectFromElement(DT_TAU) == StatusEffect::PT_SENTIENT);
		assert(GetStatusEffectFromElement(DT_COLD_NON_COMBINING) == StatusEffect::PT_CHILLED);

		assert(GetStatusEffectFromElement(DT_COLD_NON_COMBINING) == GetStatusEffectFromElement(DT_COLD));

		// Intentional failure
		assert(GetStatusEffectFromElement(DamageType::DT_TRUE) == PT_NONE);
	}
	catch (int errNum){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}