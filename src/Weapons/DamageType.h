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

	/// @brief Parse a string representation of a damage type into enum form
	/// @param name The damage type string
	/// @return 
	static DamageType ParseDamageTypeName(const std::string &name);
	/// @brief Check whether it is possible to combine the two damage types into a single combined damage type
	/// @param dt1 The first damage type to be combined
	/// @param dt2 The second damage type to be combined
	/// @return Boolean whether it is possible to combine the elements
	static bool CanCombineDamageTypes(const DamageType &dt1, const DamageType &dt2);
	/// @brief Find the damage type produced when combining two constituent elements
	/// @param dt1 The first damage type to be combined
	/// @param dt2 The second damage type to be combined
	/// @return The associated combined damage type
	static DamageType CombineDamageTypes(const DamageType &dt1, const DamageType &dt2);
	/// @brief Find what elements are required to create a singular combined element
	/// @param dt The element to be decomposed
	/// @return A vector of the required elements. If it is not possible to decompose the element, a vector length of 1 with the original element will be returned 
	static std::vector<DamageType> DecomposeCombinedElement(DamageType dt);

private:
	DamageTypeEnum _damageType;
};