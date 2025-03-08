#include "src/Mods/ModUpgradeType.h"
#include <exception>

std::string ModUpgradeType::ToString(ModUpgradeType modUpgradeType)
{
	for (size_t i = 0; i < modUpgradeStringNames.size(); i++)
	{
		if (modUpgradeType == modUpgradeStringNames[i].first)
		{
			return modUpgradeStringNames[i].second;
		}
	}
	// Failed to find the entry in the collection
	std::__throw_invalid_argument("Failed to find ModUpgradeType");
}

ModUpgradeType ModUpgradeType::ParseFromString(std::string name)
{
	for (size_t i = 0; i < modUpgradeStringNames.size(); i++)
	{
		if (name == modUpgradeStringNames[i].second)
		{
			return modUpgradeStringNames[i].first;
		}
	}
	// Failed to find string
	std::__throw_invalid_argument("Failed to parse string representation of ModUpgradeType");
}

std::vector<std::pair<ModUpgradeType, std::string>> ModUpgradeType::modUpgradeStringNames = {
	{ModUpgradeType::NO_EFFECT, "NO_EFFECT"},
	{ModUpgradeType::WEAPON_DAMAGE_AMOUNT, "WEAPON_DAMAGE_AMOUNT"},
	{ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED, "WEAPON_PERCENT_BASE_DAMAGE_ADDED"},
	{ModUpgradeType::WEAPON_FIRE_ITERATIONS, "WEAPON_FIRE_ITERATIONS"},
	{ModUpgradeType::WEAPON_FIRE_RATE, "WEAPON_FIRE_RATE"},
	{ModUpgradeType::WEAPON_RECOIL, "WEAPON_RECOIL"},
	{ModUpgradeType::WEAPON_SPREAD, "WEAPON_SPREAD"},
	{ModUpgradeType::WEAPON_ZOOM, "WEAPON_ZOOM"},
	{ModUpgradeType::WEAPON_AMMO_MAX, "WEAPON_AMMO_MAX"},
	{ModUpgradeType::WEAPON_CLIP_MAX, "WEAPON_CLIP_MAX"},
	{ModUpgradeType::WEAPON_AMMO_CONSUME_RATE, "WEAPON_AMMO_CONSUME_RATE"},
	{ModUpgradeType::WEAPON_RELOAD_SPEED, "WEAPON_RELOAD_SPEED"},
	{ModUpgradeType::WEAPON_PUNCTURE_DEPTH, "WEAPON_PUNCTURE_DEPTH"},
	{ModUpgradeType::WEAPON_CRIT_CHANCE, "WEAPON_CRIT_CHANCE"},
	{ModUpgradeType::WEAPON_CRIT_DAMAGE, "WEAPON_CRIT_DAMAGE"},
	{ModUpgradeType::WEAPON_CRIT_TIER, "WEAPON_CRIT_TIER"},
	{ModUpgradeType::WEAPON_PROC_CHANCE, "WEAPON_PROC_CHANCE"},
	{ModUpgradeType::WEAPON_PROC_DAMAGE, "WEAPON_PROC_DAMAGE"},
	{ModUpgradeType::WEAPON_PROC_TIME, "WEAPON_PROC_TIME"},
	{ModUpgradeType::WEAPON_FACTION_DAMAGE, "WEAPON_FACTION_DAMAGE"},
	{ModUpgradeType::WEAPON_WEAK_POINT_MODIFIER, "WEAPON_WEAK_POINT_MODIFIER"},
	{ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, "WEAPON_HEADSHOT_MULTIPLIER"},
	{ModUpgradeType::WEAPON_ADD_STATUS, "WEAPON_ADD_STATUS"},
	{ModUpgradeType::WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE, "WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE"},
	{ModUpgradeType::WEAPON_PROJECTILE_SPEED, "WEAPON_PROJECTILE_SPEED"},
	{ModUpgradeType::WEAPON_DAMAGE_MULTIPLIER, "WEAPON_DAMAGE_MULTIPLIER"},
	{ModUpgradeType::WEAPON_INIT_DAMAGE_MOD, "WEAPON_INIT_DAMAGE_MOD"},
	{ModUpgradeType::WEAPON_LAST_DAMAGE_MOD, "WEAPON_LAST_DAMAGE_MOD"},
	{ModUpgradeType::WARFRAME_ABILITY_STRENGTH, "WARFRAME_ABILITY_STRENGTH"},
	{ModUpgradeType::WARFRAME_ABILITY_DURATION, "WARFRAME_ABILITY_DURATION"},
	{ModUpgradeType::WARFRAME_ABILITY_EFFICIENCY, "WARFRAME_ABILITY_EFFICIENCY"},
	{ModUpgradeType::WARFRAME_ABILITY_RANGE, "WARFRAME_ABILITY_RANGE"},
};