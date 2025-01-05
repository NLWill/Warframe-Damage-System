#include "src/Services/Logging/LogService.h"
#include <iostream>

LogService::LogService()
{

}

LogService::~LogService()
{

}

void LogService::Log(string msg)
{
	std::cout << msg << std::endl;
}

void LogService::LogWarning(string msg)
{
	std::cout << "\033[93mWarning: \033[0m" << msg << std::endl;
}

void LogService::LogError(string msg)
{
	std::cout << "\033[91mError: \033[0m" << msg << std::endl;
}
