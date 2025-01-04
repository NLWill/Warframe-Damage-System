#pragma once
#include "src/Services/Logging/LoggerServiceBase.h"

class LogService : public Logger
{
public:
	LogService();
	~LogService();
	virtual void Log(string msg);
	virtual void LogWarning(string msg);
	virtual void LogError(string msg);
};