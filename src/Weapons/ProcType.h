#pragma once
#include "src/Weapons/DamageType.h"
#include "src/Services/ServiceLocator.h"

class ProcType
{
public:
	enum ProcTypeEnum
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

	ProcType() = default;
	constexpr ProcType(ProcTypeEnum aStatusEffect) : _statusEffect(aStatusEffect) {}

	// Allow switch and comparisons.
	constexpr operator ProcTypeEnum() const { return _statusEffect; }

	// Prevent usage: if(statusEffect)
	explicit operator bool() const = delete;

	// Return a string form of the proc enum
	std::string ToString();

	/// @brief Get the ProcType that the element triggering the status will create
	/// @param dt The triggering damage type
	/// @return 
	static ProcType GetProcTypeFromElement(DamageType dt);

private:
	ProcTypeEnum _statusEffect;
};