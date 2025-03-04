#pragma once
#include "src/Services/Logging/LoggerServiceBase.h"

class NullLogger : public Logger{
	public:
	NullLogger() {}
	~NullLogger() {}
	virtual void Log(string msg) {(void)msg;}
	virtual void LogWarning(string msg) {(void)msg;}
	virtual void LogError(string msg) {(void)msg;}
};