#pragma once
#include "src/Weapons/DamageType.h"

class HealthType
{
public:
	enum HealthTypeEnum
	{
		TENNO,
		GRINEER,
		KUVA_GRINEER,
		CORPUS,
		CORPUS_AMALGAM,
		INFESTED,
		INFESTED_DEIMOS,
		OROKIN,
		SENTIENT,
		NARMER,
		MURMUR,
		ZARIMAN,
		SCALDRA,
		TECHROT,
	};

	HealthType() = default;
	constexpr HealthType(HealthTypeEnum aHealthType) : _healthType(aHealthType) {}

	// Allow switch and comparisons.
	constexpr operator HealthTypeEnum() const { return _healthType; }

	// Prevent usage: if(healthtype)
	explicit operator bool() const = delete;

	static float GetHealthTypeModifier(const HealthType &healthType, const DamageType &dt);

private:
	HealthTypeEnum _healthType;
};