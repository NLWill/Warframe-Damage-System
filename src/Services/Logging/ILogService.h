#pragma once
#include<string>

class ILogService{
	public:
	virtual ~ILogService() {}
	virtual void Log(std::string msg) = 0;
	virtual void LogWarning(std::string msg) = 0;
	virtual void LogError(std::string msg) = 0;
};