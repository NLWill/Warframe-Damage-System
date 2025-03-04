#pragma once
#include <memory>
#include "src/Services\RNG\RNGServiceBase.h"
#include "src/Services\RNG\NullRNGService.h"
#include "src/Services\Logging\LoggerServiceBase.h"
#include "src/Services\Logging\NullLogService.h"

class ServiceLocator
{
public:
	static void Initialise();

	static RNG &GetRNG();
	static void Provide(shared_ptr<RNG> service);

	static Logger &GetLogger();
	static void Provide(shared_ptr<Logger> service);

private:
	static shared_ptr<RNG> rngService_;
	static shared_ptr<NullRNG> nullRngService_;

	static shared_ptr<Logger> logService_;
	static shared_ptr<NullLogger> nullLogService_;
};