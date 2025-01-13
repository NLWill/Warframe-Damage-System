#pragma once
#include "src/Weapons/DamageType.h"
#include "src/Services/ServiceLocator.h"

class StatusEffect
{
public:
	enum StatusEffectEnum
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

	StatusEffect() = default;
	constexpr StatusEffect(StatusEffectEnum aStatusEffect) : _statusEffect(aStatusEffect) {}

	// Allow switch and comparisons.
	constexpr operator StatusEffectEnum() const { return _statusEffect; }

	// Prevent usage: if(statuseffect)
	explicit operator bool() const = delete;

	std::string ToString();

	static StatusEffect GetStatusEffectFromElement(DamageType dt);

private:
	StatusEffectEnum _statusEffect;
};