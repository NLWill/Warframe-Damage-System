#include "src/Weapons/ProcType.h"
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"

std::string ProcType::ToString()
{
	switch (_statusEffect)
	{
	case PT_NONE:
		return "PT_NONE";
	case PT_KNOCKBACK:
		return "PT_KNOCKBACK";
	case PT_FRAILTY:
		return "PT_FRAILTY";
	case PT_BLEEDING:
		return "PT_BLEEDING";
	case PT_IMMOLATION:
		return "PT_IMMOLATION";
	case PT_CHILLED:
		return "PT_CHILLED";
	case PT_ELECTROCUTION:
		return "PT_ELECTROCUTION";
	case PT_POISONED:
		return "PT_POISONED";
	case PT_FLASHBANG:
		return "PT_FLASHBANG";
	case PT_CAUSTIC_BURN:
		return "PT_CAUSTIC_BURN";
	case PT_ASPHYXIATION:
		return "PT_ASPHYXIATION";
	case PT_MAGNETISED:
		return "PT_MAGNETISED";
	case PT_RAD_TOX:
		return "PT_RAD_TOX";
	case PT_INFECTED:
		return "PT_INFECTED";
	case PT_VOID:
		return "PT_VOID";
	case PT_SENTIENT:
		return "PT_SENTIENT";
	case PT_BIG_STAGGER:
		return "PT_BIG_STAGGER";
	case PT_DISARMED:
		return "PT_DISARMED";
	case PT_KNOCKED_DOWN:
		return "PT_KNOCKED_DOWN";
	case PT_LIFT_HIT:
		return "PT_LIFT_HIT";
	case PT_MICROWAVE_BURN:
		return "PT_MICROWAVE_BURN";
	case PT_PARRIED:
		return "PT_PARRIED";
	case PT_RAGDOLL:
		return "PT_RAGDOLL";
	case PT_SILENCED:
		return "PT_SILENCED";
	case PT_SLEEP:
		return "PT_SLEEP";
	case PT_GLUE:
		return "PT_GLUE";
	case PT_STAGGERED:
		return "PT_STAGGERED";
	case PT_STUNNED:
		return "PT_STUNNED";
	default:
		return "PT_" + std::to_string(_statusEffect);
	}
}

ProcType ProcType::GetProcTypeFromElement(DamageType dt)
{
	switch (dt)
	{
	case DamageType::DT_IMPACT:
		return PT_KNOCKBACK;
		break;
	case DamageType::DT_PUNCTURE:
		return PT_FRAILTY;
		break;
	case DamageType::DT_SLASH:
		return PT_BLEEDING;
		break;
	case DamageType::DT_FIRE:
	case DamageType::DT_FIRE_NON_COMBINING:
		return PT_IMMOLATION;
		break;
	case DamageType::DT_FREEZE:
	case DamageType::DT_FREEZE_NON_COMBINING:
		return PT_CHILLED;
		break;
	case DamageType::DT_ELECTRICITY:
	case DamageType::DT_ELECTRICITY_NON_COMBINING:
		return PT_ELECTROCUTION;
		break;
	case DamageType::DT_POISON:
	case DamageType::DT_POISON_NON_COMBINING:
		return PT_POISONED;
		break;
	case DamageType::DT_EXPLOSION:
		return PT_FLASHBANG;
		break;
	case DamageType::DT_RADIATION:
		return PT_RAD_TOX;
		break;
	case DamageType::DT_GAS:
		return PT_ASPHYXIATION;
		break;
	case DamageType::DT_MAGNETIC:
		return PT_MAGNETISED;
		break;
	case DamageType::DT_VIRAL:
		return PT_INFECTED;
		break;
	case DamageType::DT_CORROSIVE:
		return PT_CAUSTIC_BURN;
		break;
	case DamageType::DT_VOID:
		return PT_VOID;
		break;
	case DamageType::DT_TAU:
		return PT_SENTIENT;
		break;
	default:
		ServiceLocator::GetService<ILogService>()->LogError("Unhandled damage type when trying to retreive the correponding status type");
		return PT_NONE;
		break;
	}
}