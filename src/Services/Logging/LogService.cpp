#include "src/Services/Logging/LogService.h"
#include <iostream>
#include "LogService.h"

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
	std::cout << "Warning: " << msg << std::endl;
}

void LogService::LogError(string msg)
{
	std::cout << "Error: " << msg << std::endl;
}
