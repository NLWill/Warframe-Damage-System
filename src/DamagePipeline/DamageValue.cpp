#include "src/DamagePipeline/DamageValue.h"

DamageValue::DamageValue(DamageType _type, float _value)
{
	damageType = _type;
	value = _value;
}

DamageValue::DamageValue(const DamageValue &other)
{
	damageType = other.damageType;
	value = other.value;
}

DamageValue& DamageValue::operator=(const DamageValue &other)
{
	this->damageType = other.damageType;
	this->value = other.value;
	return *this;
}

DamageValue& DamageValue::operator*(const float &mult)
{
	return *this *= mult;
}
DamageValue& DamageValue::operator*=(const float &mult)
{
	value *= mult;
	return *this;
}

DamageValue& DamageValue::operator/(const float &divisor)
{
	return *this /= divisor;
}
DamageValue& DamageValue::operator/=(const float &divisor)
{
	value /= divisor;
	return *this;
}

DamageValue& DamageValue::operator+(const float &addValue)
{
	return *this += addValue;
}
DamageValue& DamageValue::operator+=(const float &addValue)
{
	value += addValue;
	return *this;
}

DamageValue& DamageValue::operator-(const float &subtractValue)
{
	return *this  -= subtractValue;
}
DamageValue& DamageValue::operator-=(const float &subtractValue)
{
	value -= subtractValue;
	return *this;
}
