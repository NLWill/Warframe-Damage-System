#include "src/Weapons/StatusEffect.h"
#include "StatusEffect.h"

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
