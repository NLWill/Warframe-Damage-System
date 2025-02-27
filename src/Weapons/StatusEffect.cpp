#include "src/Weapons/StatusEffect.h"

StatusEffect::StatusEffect()
{
	procType = ProcType::PT_NONE;
	damage = 0;
}

StatusEffect::StatusEffect(ProcType procType, float damage)
{
	this->procType = procType;
	this->damage = damage;
}

float StatusEffect::GetStatusDuration(ProcType procType)
{
	switch (procType)
	{
	case ProcType::PT_KNOCKBACK:
		return 6;
	case ProcType::PT_FRAILTY:
		return 10;
	case ProcType::PT_BLEEDING:
		return 6;
	case ProcType::PT_IMMOLATION:
		return 6;
	case ProcType::PT_CHILLED:
		return 6;
	case ProcType::PT_ELECTROCUTION:
		return 6;
	case ProcType::PT_POISONED:
		return 6;
	case ProcType::PT_FLASHBANG:
		return 1.5;
	case ProcType::PT_CAUSTIC_BURN:
		return 8;
	case ProcType::PT_ASPHYXIATION:
		return 6;
	case ProcType::PT_MAGNETISED:
		return 6;
	case ProcType::PT_RAD_TOX:
		return 12;
	case ProcType::PT_INFECTED:
		return 6;
	case ProcType::PT_VOID:
		return 3;
	case ProcType::PT_SENTIENT:
		return 8;
	case ProcType::PT_BIG_STAGGER:
		return 1;
	case ProcType::PT_DISARMED:
		return INT32_MAX;
	case ProcType::PT_KNOCKED_DOWN:
		return 2;
	case ProcType::PT_LIFT_HIT:
		return 1;
	case ProcType::PT_MICROWAVE_BURN:
		return INT32_MAX;
	case ProcType::PT_PARRIED:
		return 1;
	case ProcType::PT_RAGDOLL:
		return 5;
	case ProcType::PT_SILENCED:
		return INT32_MAX;
	case ProcType::PT_SLEEP:
		return INT32_MAX;
	case ProcType::PT_GLUE:
		return INT32_MAX;
	case ProcType::PT_STAGGERED:
		return 1;
	case ProcType::PT_STUNNED:
		return 2;
	default:
		return 0;
	}
}
