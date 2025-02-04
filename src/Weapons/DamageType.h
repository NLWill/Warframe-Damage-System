#pragma once
#include <string>
#include <vector>

class DamageType
{
public:
	enum DamageTypeEnum
	{
		DT_ANY,
		DT_IMPACT,
		DT_PUNCTURE,
		DT_SLASH,
		DT_FIRE,
		DT_FREEZE,
		DT_ELECTRICITY,
		DT_POISON,
		DT_FIRE_NON_COMBINING,
		DT_FREEZE_NON_COMBINING,
		DT_ELECTRICITY_NON_COMBINING,
		DT_POISON_NON_COMBINING,
		DT_EXPLOSION,
		DT_RADIATION,
		DT_GAS,
		DT_MAGNETIC,
		DT_VIRAL,
		DT_CORROSIVE,
		DT_VOID,
		DT_TAU,
		DT_TRUE
	};

	DamageType() = default;
	constexpr DamageType(DamageTypeEnum aDamageType) : _damageType(aDamageType) {}

	// Allow switch and comparisons.
	constexpr operator DamageTypeEnum() const { return _damageType; }

	// Prevent usage: if(damagetype)
	explicit operator bool() const = delete;

	std::string ToString();

	static DamageType ParseDamageTypeName(const std::string &name);
	static DamageType CombineDamageTypes(const DamageType &dt1, const DamageType &dt2);
	static std::vector<DamageType> DecomposeCombinedElement(DamageType dt);

private:
	DamageTypeEnum _damageType;
};