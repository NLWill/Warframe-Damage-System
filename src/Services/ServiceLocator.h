#include "src\Services\RNG\RNGServiceBase.h"
#include "src\Services\RNG\NullRNGService.h"

class ServiceLocator{
public:
  static void Initialise();

  static RNG& GetRNG();

  static void Provide(RNG* service);

private:
  static RNG* service;
  static NullRNG nullService_;
};