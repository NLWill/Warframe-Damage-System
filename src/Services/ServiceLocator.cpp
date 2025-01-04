#include "src/Services/ServiceLocator.h"

class ServiceLocator{
public:
  static void Initialise() {
     rngService_ = &nullRngService_; 
     logService_ = &nullLogService_;
  }

  static RNG& GetRNG() { return *rngService_; };

  static void Provide(RNG* service)
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

  static Logger& GetLogger() { return *logService_; };

  static void Provide(Logger* service)
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

private:
  static RNG* rngService_;
  static NullRNG nullRngService_;

  static Logger* logService_;
  static NullLogger nullLogService_;
};