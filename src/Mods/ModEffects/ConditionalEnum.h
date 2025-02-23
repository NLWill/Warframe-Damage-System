#pragma once
#include <string>

class Conditional
{
public:
	enum ConditionalEnum
	{
		onFire,
		onHit,
		onHeadshot,
		onKill,
		onHeadshotKill,
		onReload,
		onReloadFromEmpty,
		whileWallLatch,
		whileAimGlide,
		whileSlide,
		onAbilityCast,
		onEquip,
		whileChanneledAbility,
		onShieldBreak,
		whileOvershields
	};

	Conditional() = default;
	constexpr Conditional(ConditionalEnum aConditional) : _conditional(aConditional) {}

	// Allow switch and comparisons.
	constexpr operator ConditionalEnum() const { return _conditional; }

	// Prevent usage: if(conditional)
	explicit operator bool() const = delete;

private:
	ConditionalEnum _conditional;
};