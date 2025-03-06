#include "src/Services/Logging/LogService.h"
#include <iostream>

LogService::LogService()
{

}

LogService::~LogService()
{

}

void LogService::Log(std::string msg)
{
	std::cout << msg << std::endl;
}

void LogService::LogWarning(std::string msg)
{
	std::cout << "\033[93mWarning: \033[0m" << msg << std::endl;
}

void LogService::LogError(std::string msg)
{
	std::cout << "\033[91mError: \033[0m" << msg << std::endl;
}
