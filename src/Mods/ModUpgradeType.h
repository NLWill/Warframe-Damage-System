#pragma once

class ModUpgradeType
{
public:
	enum ModUpgradeTypeEnum
	{
		WEAPON_DAMAGE_AMOUNT,
		WEAPON_PERCENT_BASE_DAMAGE_ADDED,
		WEAPON_MULTISHOT,
		WEAPON_FIRE_RATE,
		WEAPON_RECOIL,
		WEAPON_SPREAD,
		WEAPON_ZOOM,
		WEAPON_AMMO_MAXIMUM,
		WEAPON_MAGAZINE_CAPACITY,
		WEAPON_AMMO_CONSUME_RATE,
		WEAPON_RELOAD_SPEED,
		WEAPON_PUNCH_THROUGH,
		WEAPON_CRIT_CHANCE,
		WEAPON_CRIT_DAMAGE,
		WEAPON_CRIT_TIER,
		WEAPON_STATUS_CHANCE,
		WEAPON_STATUS_DAMAGE,
		WEAPON_STATUS_DURATION,
		WEAPON_FACTION_DAMAGE,
		WEAPON_HITZONE_MODIFIER,
		WEAPON_ADD_STATUS,
		WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE,
		WEAPON_PROJECTILE_SPEED,
		WEAPON_DAMAGE_MULTIPLIER,
		WEAPON_INIT_DAMAGE_MOD, // Primed Chamber
		WEAPON_LAST_DAMAGE_MOD, // Synth Charge
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

private:
	ModUpgradeTypeEnum _modUpgradeType;
};