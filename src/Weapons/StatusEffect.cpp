#include "src/Weapons/StatusEffect.h"
#include <iostream>

#define DEBUG_STATUS_EFFECT false

StatusEffect::StatusEffect()
{
	procType = ProcType::PT_NONE;
	damage = 0;
}

StatusEffect::StatusEffect(ProcType procType, shared_ptr<DamageInstanceModEffectInterface> originatingDamageInstance, float baseDamage)
{
#if DEBUG_STATUS_EFFECT
	std::cout << "Making status effect" << std::endl;
	std::cout << "Base damage = " << baseDamage << std::endl;
#endif
	this->procType = procType;
	remainingDuration = GetStatusDuration(procType) * originatingDamageInstance->GetStatusDurationMultiplier();
#if DEBUG_STATUS_EFFECT
	std::cout << "Remaining duration = " << remainingDuration << std::endl;
#endif

	// Find the damage type that the status effect deals
	damageType = GetDamageTypeOfStatusEffect(procType);
#if DEBUG_STATUS_EFFECT
	std::cout << "Damage type = " << damageType.ToString() << std::endl;
#endif

	switch (procType)
	{
	case ProcType::PT_ELECTROCUTION:
	case ProcType::PT_ASPHYXIATION:
		// Only Electicity and Gas status effects can damage individual hitzones
		targetBodyPart = originatingDamageInstance->GetTargetBodyPart();
		break;
	default:
		// Most status effects target centre of mass
		targetBodyPart = "Body";
		break;
	}
#if DEBUG_STATUS_EFFECT
	std::cout << "Target body part = " << targetBodyPart << std::endl;
#endif

	float elementalBonus;
	switch (procType)
	{
	case ProcType::PT_BLEEDING:
	case ProcType::PT_ASPHYXIATION:
	case ProcType::PT_FLASHBANG:
		elementalBonus = 0;
		break;
	case ProcType::PT_IMMOLATION:
		elementalBonus = originatingDamageInstance->GetElementalWeights()[DamageType::DT_FIRE];
		break;
	case ProcType::PT_ELECTROCUTION:
		elementalBonus = originatingDamageInstance->GetElementalWeights()[DamageType::DT_ELECTRICITY];
		break;
	case ProcType::PT_POISONED:
		elementalBonus = originatingDamageInstance->GetElementalWeights()[DamageType::DT_POISON];
		break;
	default:
		elementalBonus = 0;
		break;
	}
#if DEBUG_STATUS_EFFECT
	std::cout << "Elemental bonus = " << elementalBonus << std::endl;
#endif

	float scalingMultiplier;
	switch (procType)
	{
	case ProcType::PT_BLEEDING:
		scalingMultiplier = 0.35;
		break;
	case ProcType::PT_FLASHBANG:
		scalingMultiplier = 0.3;
		break;
	case ProcType::PT_IMMOLATION:
	case ProcType::PT_ELECTROCUTION:
	case ProcType::PT_POISONED:
	case ProcType::PT_ASPHYXIATION:
		scalingMultiplier = 0.5;
		break;
	default:
		// Most status effects do not do any damage
		scalingMultiplier = 0;
		break;
	}
#if DEBUG_STATUS_EFFECT
	std::cout << "Scaling multiplier = " << scalingMultiplier << std::endl;
#endif

	damage = scalingMultiplier * baseDamage * originatingDamageInstance->GetStatusDamageMultiplier() * (1 + elementalBonus);
#if DEBUG_STATUS_EFFECT
	std::cout << "Base damage of status effect before damaging the target = " << damage << std::endl;
#endif
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

int StatusEffect::GetNumberOfDamageTicks()
{
	int numberOfDamageTicks = std::ceil(remainingDuration - GetTimeBeforeFirstDamageTick(procType));
#if DEBUG_STATUS_EFFECT
	std::cout << "Number of damage ticks = " << numberOfDamageTicks << std::endl;
#endif
	return numberOfDamageTicks;
}

bool StatusEffect::IsDamagingStatusEffect(ProcType procType)
{
	switch (procType)
	{
	case ProcType::PT_BLEEDING:
	case ProcType::PT_IMMOLATION:
	case ProcType::PT_POISONED:
	case ProcType::PT_ASPHYXIATION:
	case ProcType::PT_ELECTROCUTION:
	case ProcType::PT_FLASHBANG:
		return true;
		break;
	default:
		return false;
		break;
	}
}

DamageType StatusEffect::GetDamageTypeOfStatusEffect(ProcType procType)
{
	switch (procType)
	{
	case ProcType::PT_BLEEDING:
		return DamageType::DT_TRUE;
	case ProcType::PT_ASPHYXIATION:
		return DamageType::DT_GAS;
	case ProcType::PT_IMMOLATION:
		return DamageType::DT_FIRE;
	case ProcType::PT_ELECTROCUTION:
		return DamageType::DT_ELECTRICITY;
	case ProcType::PT_POISONED:
		return DamageType::DT_POISON;
	case ProcType::PT_FLASHBANG:
		return DamageType::DT_EXPLOSION;
	default:
		return DamageType::DT_ANY;
		break;
	}
}

float StatusEffect::GetTimeBeforeFirstDamageTick(ProcType procType)
{
	// Add minor delays either side of the 1 second mark to ensure procs only trigger 6 times under normal conditions
	switch (procType)
	{
	case ProcType::PT_BLEEDING:
	case ProcType::PT_IMMOLATION:
	case ProcType::PT_POISONED:
		return 0.99;
	case ProcType::PT_ASPHYXIATION:
	case ProcType::PT_ELECTROCUTION:
		return 0;
	case ProcType::PT_FLASHBANG:
		return 1.49;
	default:
		return 0;
		break;
	}
	return 0.0f;
}
