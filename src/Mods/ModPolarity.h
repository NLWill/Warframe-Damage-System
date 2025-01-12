#pragma once

class ModPolarity
{
public:
	enum ModPolarityEnum
	{
		NONE,
		MADURAI,
		VAZARIN,
		UNAIRU,
		NARAMON,
		ZENURIK,
		PENJAGA,
		UMBRAL,
		KONEKSI,
		UNIVERSAL
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