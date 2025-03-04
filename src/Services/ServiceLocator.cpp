#include "src/Services/ServiceLocator.h"
#include <iostream>
#include <string>

void ServiceLocator::Initialise()
{
	nullRngService_ = make_shared<NullRNG>();
	nullLogService_ = make_shared<NullLogger>();

	rngService_ = nullRngService_;
	logService_ = nullLogService_;
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

void ServiceLocator::Provide(shared_ptr<RNG> service)
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

void ServiceLocator::Provide(shared_ptr<Logger> service)
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

shared_ptr<RNG> ServiceLocator::rngService_;
shared_ptr<NullRNG> ServiceLocator::nullRngService_;

shared_ptr<Logger> ServiceLocator::logService_;
shared_ptr<NullLogger> ServiceLocator::nullLogService_;