#include "src/Services/ServiceLocator.h"

class ServiceLocator{
public:
  static void Initialise() { service_ = &nullService_; }

  static RNG& GetRNG() { return *service_; };

  static void Provide(RNG* service)
  {
    if (service == NULL)
    {
      // Revert to null service.
      service_ = &nullService_;
    }
    else
    {
      service_ = service;
    }
  }

private:
  static RNG* service_;
  static NullRNG nullService_;
};