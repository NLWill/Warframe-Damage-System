#include "src/DamagePipeline/DamageValue.h"

DamageValue::DamageValue(DamageType _type, float _value)
{
	type = _type;
	value = _value;
}

DamageValue& DamageValue::operator=(const DamageValue &other)
{
	this->type = other.type;
	this->value = other.value;
	return *this;
}

DamageValue& DamageValue::operator*(const float &mult)
{
	value *= mult;
	return *this;
}

DamageValue& DamageValue::operator/(const float &divisor)
{
	value /= divisor;
	return *this;
}

DamageValue& DamageValue::operator+(const float &other)
{
	value += other;
	return *this;
}

DamageValue& DamageValue::operator-(const float &mult)
{
	value -= mult;
	return *this;
}
