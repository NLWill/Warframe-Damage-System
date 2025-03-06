#pragma once
#include "src/Services/Logging/ILogService.h"

class LogService : public ILogService
{
public:
	LogService();
	~LogService();
	virtual void Log(std::string msg);
	virtual void LogWarning(std::string msg);
	virtual void LogError(std::string msg);
};