#include "src/Services/ServiceLocator.h"
#include <iostream>
#include <string>

void ServiceLocator::Initialise()
{
	nullRngService_ = std::make_shared<NullRNG>();
	nullLogService_ = std::make_shared<NullLogger>();

	rngService_ = nullRngService_;
	logService_ = nullLogService_;
}

IRNGService &ServiceLocator::GetRNG()
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

void ServiceLocator::Provide(std::shared_ptr<IRNGService> service)
{
	if (service == NULL)
	{
		// Revert to null service.
		rngService_ = nullRngService_;
	}
	else
	{
		rngService_ = service;
	}
}

ILogService &ServiceLocator::GetLogger()
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

void ServiceLocator::Provide(std::shared_ptr<ILogService> service)
{
	if (service == NULL)
	{
		// Revert to null service.
		logService_ = nullLogService_;
	}
	else
	{
		logService_ = service;
	}
}

std::shared_ptr<IRNGService> ServiceLocator::rngService_;
std::shared_ptr<NullRNG> ServiceLocator::nullRngService_;

std::shared_ptr<ILogService> ServiceLocator::logService_;
std::shared_ptr<NullLogger> ServiceLocator::nullLogService_;