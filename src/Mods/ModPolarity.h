#pragma once

class ModPolarity
{
public:
	enum ModPolarityEnum
	{
		AP_UNIVERSAL,	// No mod polarity
		AP_ATTACK,		// Madurai
		AP_DEFENSE,		// Vazarin
		AP_WARD,		// Unairu
		AP_TACTIC,		// Naramon
		AP_POWER,		// Zenurik
		AP_PRECEPT,		// Penjaga
		AP_UMBRA,		// Umbral
		AP_FUSION,		// Koneksi, Fusion core
		AP_ANY			// Universal
	};

	ModPolarity() = default;
	constexpr ModPolarity(ModPolarityEnum aModPolarity) : _modPolarity(aModPolarity) {}

	// Allow switch and comparisons.
	constexpr operator ModPolarityEnum() const { return _modPolarity; }

	// Prevent usage: if(modpolarity)
	explicit operator bool() const = delete;



private:
	ModPolarityEnum _modPolarity;
};