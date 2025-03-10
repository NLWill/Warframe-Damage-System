#pragma once
#include <string>
#include <vector>

class ModUpgradeType
{
public:
	enum ModUpgradeTypeEnum
	{
		NO_EFFECT,
		WEAPON_DAMAGE_AMOUNT,
		WEAPON_PERCENT_BASE_DAMAGE_ADDED,
		WEAPON_FIRE_ITERATIONS,
		WEAPON_FIRE_RATE,
		WEAPON_RECOIL,
		WEAPON_SPREAD,
		WEAPON_ZOOM,
		WEAPON_AMMO_MAX,
		WEAPON_CLIP_MAX,
		WEAPON_AMMO_CONSUME_RATE,
		WEAPON_RELOAD_SPEED,
		WEAPON_PUNCTURE_DEPTH,
		WEAPON_CRIT_CHANCE,
		WEAPON_CRIT_DAMAGE,
		WEAPON_CRIT_TIER,
		WEAPON_PROC_CHANCE,
		WEAPON_PROC_DAMAGE,
		WEAPON_PROC_TIME,
		WEAPON_WEAK_POINT_MODIFIER,
		WEAPON_HEADSHOT_MULTIPLIER,
		WEAPON_ADD_STATUS,
		WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE,
		WEAPON_PROJECTILE_SPEED,
		WEAPON_DAMAGE_MULTIPLIER,
		WEAPON_INIT_DAMAGE_MOD, // Primed Chamber
		WEAPON_LAST_DAMAGE_MOD, // Synth Charge
		GAMEPLAY_FACTION_DAMAGE,
		WARFRAME_ABILITY_STRENGTH,
		WARFRAME_ABILITY_DURATION,
		WARFRAME_ABILITY_EFFICIENCY,
		WARFRAME_ABILITY_RANGE,
	};

	ModUpgradeType() = default;
	constexpr ModUpgradeType(ModUpgradeTypeEnum aModUpgradeType) : _modUpgradeType(aModUpgradeType) {}

	// Allow switch and comparisons.
	constexpr operator ModUpgradeTypeEnum() const { return _modUpgradeType; }

	// Prevent usage: if(modupgradetype)
	explicit operator bool() const = delete;

	// Convert Enum into string form for output in the console
	static std::string ToString(ModUpgradeType modUpgradeType);
	// Convert string representation to Enum form
	static ModUpgradeType ParseFromString(std::string name);

private:
	ModUpgradeTypeEnum _modUpgradeType;

	/// @brief A pairing of enum values and strings for quick parsing and string conversion
	static std::vector<std::pair<ModUpgradeType, std::string>> modUpgradeStringNames;
};