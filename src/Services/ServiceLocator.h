#pragma once
#include <memory>
#include "src/Services\RNG\IRNGService.h"
#include "src/Services\RNG\NullRNGService.h"
#include "src/Services\Logging\ILogService.h"
#include "src/Services\Logging\NullLogService.h"

class ServiceLocator
{
public:
	static void Initialise();

	static IRNGService &GetRNG();
	static void Provide(std::shared_ptr<IRNGService> service);

	static ILogService &GetLogger();
	static void Provide(std::shared_ptr<ILogService> service);

private:
	static std::shared_ptr<IRNGService> rngService_;
	static std::shared_ptr<NullRNG> nullRngService_;

	static std::shared_ptr<ILogService> logService_;
	static std::shared_ptr<NullLogger> nullLogService_;
};