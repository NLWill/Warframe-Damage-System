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
		assert(ProcType::GetProcTypeFromElement(DamageType::DT_EXPLOSION) == ProcType::PT_FLASHBANG);
		assert(ProcType::GetProcTypeFromElement(DamageType::DT_FIRE) == ProcType::PT_IMMOLATION);
		assert(ProcType::GetProcTypeFromElement(DamageType::DT_VOID) == ProcType::PT_VOID);
		assert(ProcType::GetProcTypeFromElement(DamageType::DT_CORROSIVE) == ProcType::PT_CAUSTIC_BURN);
		assert(ProcType::GetProcTypeFromElement(DamageType::DT_TAU) == ProcType::PT_SENTIENT);
		assert(ProcType::GetProcTypeFromElement(DamageType::DT_FREEZE_NON_COMBINING) == ProcType::PT_CHILLED);

		assert(ProcType::GetProcTypeFromElement(DamageType::DT_FREEZE_NON_COMBINING) == ProcType::GetProcTypeFromElement(DamageType::DT_FREEZE));

		// Intentional failure
		assert(ProcType::GetProcTypeFromElement(DamageType::DT_TRUE) == ProcType::PT_NONE);
	}
	catch (int errNum){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}