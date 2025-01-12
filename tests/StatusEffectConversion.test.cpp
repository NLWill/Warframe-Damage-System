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
		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_BLAST) == StatusEffect::PT_FLASHBANG);
		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_HEAT) == StatusEffect::PT_IMMOLATION);
		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_VOID) == StatusEffect::PT_VOID);
		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_CORROSIVE) == StatusEffect::PT_CAUSTIC_BURN);
		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_TAU) == StatusEffect::PT_SENTIENT);
		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_COLD_NON_COMBINING) == StatusEffect::PT_CHILLED);

		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_COLD_NON_COMBINING) == StatusEffect::GetStatusEffectFromElement(DamageType::DT_COLD));

		// Intentional failure
		assert(StatusEffect::GetStatusEffectFromElement(DamageType::DT_TRUE) == StatusEffect::PT_NONE);
	}
	catch (int errNum){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}