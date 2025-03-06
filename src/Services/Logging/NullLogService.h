#pragma once
#include "src/Services/Logging/ILogService.h"

class NullLogger : public ILogService{
	public:
	NullLogger() {}
	~NullLogger() {}
	virtual void Log(std::string msg) {(void)msg;}
	virtual void LogWarning(std::string msg) {(void)msg;}
	virtual void LogError(std::string msg) {(void)msg;}
};