#include "src/Services/ServiceLocator.h"

void ServiceLocator::Initialise()
{
  rngService_ = &nullRngService_;
  logService_ = &nullLogService_;
}

RNG &ServiceLocator::GetRNG() { return *rngService_; };

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

Logger &ServiceLocator::GetLogger() { return *logService_; };

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

RNG* ServiceLocator::rngService_;
NullRNG ServiceLocator::nullRngService_;

Logger* ServiceLocator::logService_;
NullLogger ServiceLocator::nullLogService_;