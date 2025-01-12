#pragma once
#include "src/Weapons/DamageType.h"

class HealthType
{
public:
	enum HealthTypeEnum
	{
		HEALTH_TYPE_TENNO,
		HEALTH_TYPE_GRINEER,
		HEALTH_TYPE_KUVA_GRINEER,
		HEALTH_TYPE_CORPUS,
		HEALTH_TYPE_CORPUS_AMALGAM,
		HEALTH_TYPE_INFESTED,
		HEALTH_TYPE_INFESTED_DEIMOS,
		HEALTH_TYPE_OROKIN,
		HEALTH_TYPE_SENTIENT,
		HEALTH_TYPE_NARMER,
		HEALTH_TYPE_MURMUR,
		HEALTH_TYPE_ZARIMAN,
		HEALTH_TYPE_SCALDRA,
		HEALTH_TYPE_TECHROT,
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