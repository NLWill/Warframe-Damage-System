#pragma once

class Faction
{
public:
	enum FactionEnum
	{
		FAC_NONE,
		FAC_TENNO,
		FAC_GRINEER,
		FAC_CORPUS,
		FAC_INFESTED,
		FAC_OROKIN,
		FAC_SENTIENT,
		FAC_STALKER,
		FAC_NARMER,
		FAC_MURMUR,
		FAC_SCALDRA,
		FAC_TECHROT,
		FAC_SYNDICATES,
		FAC_WILD
	};

	Faction() = default;
	constexpr Faction(FactionEnum aFaction) : _faction(aFaction) {}

	// Allow switch and comparisons.
	constexpr operator FactionEnum() const { return _faction; }

	// Prevent usage: if(faction)
	explicit operator bool() const = delete;

private:
	FactionEnum _faction;
};