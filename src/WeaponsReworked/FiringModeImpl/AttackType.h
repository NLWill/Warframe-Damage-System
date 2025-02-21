#pragma once

class HitType
{
public:
	enum HitTypeEnum
	{
		HITSCAN,
		PROJECTILE,
		RADIAL,
		RADIAL_ON_MISS
	};

	HitType() = default;
	constexpr HitType(HitTypeEnum aHitType) : _hitType(aHitType) {}

	// Allow switch and comparisons.
	constexpr operator HitTypeEnum() const { return _hitType; }

	// Prevent usage: if(statusEffect)
	explicit operator bool() const = delete;

private:
	HitTypeEnum _hitType;
};