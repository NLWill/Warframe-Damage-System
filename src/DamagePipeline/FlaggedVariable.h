#pragma once

template <typename T>
struct FlaggedVariable
{
	FlaggedVariable<T>() { dirtyFlag = true; }
	explicit FlaggedVariable<T>(T _value)
	{
		value = _value;
		dirtyFlag = true;
	}

	T Get() { return value; }
	void Set(T _value)
	{
		value = _value;
		dirtyFlag = false;
	}
	bool dirtyFlag;

private:
	T value;
};