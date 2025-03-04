#pragma once

template <typename T>
struct FlaggedVariable
{
	FlaggedVariable() { needsToBeCalculated = true; }
	explicit FlaggedVariable(T _value)
	{
		value = _value;
		needsToBeCalculated = true;
	}

	T Get() { return value; }
	void Set(T _value)
	{
		value = _value;
	}
	bool needsToBeCalculated;

private:
	T value;
};