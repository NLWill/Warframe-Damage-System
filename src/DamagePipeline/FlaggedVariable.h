#pragma once

template <typename T>
struct FlaggedVariable
{
	FlaggedVariable<T>() { needsToBeCalculated = true; }
	explicit FlaggedVariable<T>(T _value)
	{
		value = _value;
		needsToBeCalculated = true;
	}

	T Get() { return value; }
	void Set(T _value)
	{
		value = _value;
		needsToBeCalculated = false;
	}
	bool needsToBeCalculated;

private:
	T value;
};