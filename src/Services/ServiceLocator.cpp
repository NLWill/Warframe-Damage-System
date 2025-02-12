#include "src/Services/ServiceLocator.h"
#include <iostream>
#include <string>

void ServiceLocator::Initialise()
{
	rngService_ = &nullRngService_;
	logService_ = &nullLogService_;
}

RNG &ServiceLocator::GetRNG()
{
	if (logService_ != nullptr)
	{
		return *rngService_;
	}
	else
	{
		std::string errorMsg = "Call to GetRNG for uninstantiated ServiceLocator";
		std::cout << errorMsg << std::endl;
		throw errorMsg;
	}
};

void ServiceLocator::Provide(RNG *service)
{
	if (service == NULL)
	{
		// Revert to null service.
		rngService_ = &nullRngService_;
	}
	else
	{
		rngService_ = service;
	}
}

Logger &ServiceLocator::GetLogger()
{
	if (logService_ != nullptr)
	{
		return *logService_;
	}
	else
	{
		std::string errorMsg = "Call to GetLogger for uninstantiated ServiceLocator";
		std::cout << errorMsg << std::endl;
		throw errorMsg;
	}
}

void ServiceLocator::Provide(Logger *service)
{
	if (service == NULL)
	{
		// Revert to null service.
		logService_ = &nullLogService_;
	}
	else
	{
		logService_ = service;
	}
}

RNG *ServiceLocator::rngService_;
NullRNG ServiceLocator::nullRngService_;

Logger *ServiceLocator::logService_;
NullLogger ServiceLocator::nullLogService_;