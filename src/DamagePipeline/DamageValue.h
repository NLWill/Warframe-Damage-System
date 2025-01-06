#pragma once
#include "src/Weapons/DamageType.h"

struct DamageValue{
	public:
	DamageType type;
	float value;

	DamageValue(DamageType _type, float _value);

	DamageValue& operator=(const DamageValue& other);
	DamageValue& operator*(const float& mult);
	DamageValue& operator/(const float& divisor);
	DamageValue& operator+(const float& other);
	DamageValue& operator-(const float& mult);
};