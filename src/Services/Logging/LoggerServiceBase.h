#pragma once
#include<string>
using namespace std;

class Logger{
	public:
	virtual ~Logger() {}
	virtual void Log(string msg) = 0;
	virtual void LogWarning(string msg) = 0;
	virtual void LogError(string msg) = 0;
};