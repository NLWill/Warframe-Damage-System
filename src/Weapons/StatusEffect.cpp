#include "src/Weapons/StatusEffect.h"

StatusEffect StatusEffect::GetStatusEffectFromElement(DamageType dt)
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
	case DamageType::DT_HEAT:
	case DamageType::DT_HEAT_NON_COMBINING:
		return PT_IMMOLATION;
		break;
	case DamageType::DT_COLD:
	case DamageType::DT_COLD_NON_COMBINING:
		return PT_CHILLED;
		break;
	case DamageType::DT_ELECTRICITY:
	case DamageType::DT_ELECTRICITY_NON_COMBINING:
		return PT_ELECTROCUTION;
		break;
	case DamageType::DT_TOXIN:
	case DamageType::DT_TOXIN_NON_COMBINING:
		return PT_POISONED;
		break;
	case DamageType::DT_BLAST:
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
		ServiceLocator::GetLogger().LogError("Unhandled damage type when trying to retreive the correponding status type");
		return PT_NONE;
		break;
	}
}