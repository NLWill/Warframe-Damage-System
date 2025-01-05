#include "src/Services\RNG\RNGServiceBase.h"
#include "src/Services\RNG\NullRNGService.h"
#include "src/Services\Logging\LoggerServiceBase.h"
#include "src/Services\Logging\NullLogService.h"

class ServiceLocator{
public:
  static void Initialise();

  static RNG& GetRNG();
  static void Provide(RNG* service);

  static Logger& GetLogger();
  static void Provide(Logger* service);

private:
  static RNG* rngService_;
  static NullRNG nullRngService_;

  static Logger* logService_;
  static NullLogger nullLogService_;
};