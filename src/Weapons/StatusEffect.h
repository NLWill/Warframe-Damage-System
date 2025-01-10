#pragma once
#include "src/Weapons/DamageType.h"
#include "src/Services/ServiceLocator.h"

enum StatusEffect
{
	PT_NONE,
	PT_KNOCKBACK,
	PT_FRAILTY,
	PT_BLEEDING,
	PT_IMMOLATION,
	PT_CHILLED,
	PT_ELECTROCUTION,
	PT_POISONED,
	PT_FLASHBANG,
	PT_CAUSTIC_BURN,
	PT_ASPHYXIATION,
	PT_MAGNETISED,
	PT_RAD_TOX,
	PT_INFECTED,
	PT_VOID,
	PT_SENTIENT,
	PT_BIG_STAGGER,
	PT_DISARMED,
	PT_KNOCKED_DOWN,
	PT_LIFT_HIT,
	PT_MICROWAVE_BURN,
	PT_PARRIED,
	PT_RAGDOLL,
	PT_SILENCED,
	PT_SLEEP,
	PT_GLUE,
	PT_STAGGERED,
	PT_STUNNED
};

static StatusEffect GetStatusEffectFromElement(DamageType dt)
{
	switch (dt)
	{
	case DT_IMPACT:
		return PT_KNOCKBACK;
		break;
	case DT_PUNCTURE:
		return PT_FRAILTY;
		break;
	case DT_SLASH:
		return PT_BLEEDING;
		break;
	case DT_HEAT:
	case DT_HEAT_NON_COMBINING:
		return PT_IMMOLATION;
		break;
	case DT_COLD:
	case DT_COLD_NON_COMBINING:
		return PT_CHILLED;
		break;
	case DT_ELECTRICITY:
	case DT_ELECTRICITY_NON_COMBINING:
		return PT_ELECTROCUTION;
		break;
	case DT_TOXIN:
	case DT_TOXIN_NON_COMBINING:
		return PT_POISONED;
		break;
	case DT_BLAST:
		return PT_FLASHBANG;
		break;
	case DT_RADIATION:
		return PT_RAD_TOX;
		break;
	case DT_GAS:
		return PT_ASPHYXIATION;
		break;
	case DT_MAGNETIC:
		return PT_MAGNETISED;
		break;
	case DT_VIRAL:
		return PT_INFECTED;
		break;
	case DT_CORROSIVE:
		return PT_CAUSTIC_BURN;
		break;
	case DT_VOID:
		return PT_VOID;
		break;
	case DT_TAU:
		return PT_SENTIENT;
		break;
	default:
		ServiceLocator::GetLogger().LogError("Unhandled damage type when trying to retreive the correponding status type");
		return PT_NONE;
		break;
	}
}