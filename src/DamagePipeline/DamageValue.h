#pragma once
#include "src/Weapons/DamageType.h"

struct DamageValue{
	public:
	DamageType damageType;
	float value;

	DamageValue(DamageType _type, float _value);
	DamageValue(const DamageValue &other);

	DamageValue& operator=(const DamageValue& other);
	DamageValue& operator*(const float& mult);
	DamageValue& operator/(const float& divisor);
	DamageValue& operator+(const float& addValue);
	DamageValue& operator-(const float& subtractValue);
	DamageValue& operator*=(const float& mult);
	DamageValue& operator/=(const float& divisor);
	DamageValue& operator+=(const float& addValue);
	DamageValue& operator-=(const float& subtractValue);

};