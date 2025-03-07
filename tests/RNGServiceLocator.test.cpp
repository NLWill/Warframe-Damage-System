#include "../src/Services/RNG/RNGService.h"
#include "../src/Services/ServiceLocator.h"
#include "../src/Services/RNG/NullRNGService.h"
#include <iostream>

static void assert(bool _result);

int main()
{
	auto nullRNGService = std::make_shared<NullRNG>();
	ServiceLocator::RegisterService<IRNGService>(nullRNGService);
	try
	{
		assert(ServiceLocator::GetService<IRNGService>()->RandomInt() == 0);

		ServiceLocator::UnregisterService<IRNGService>();
		auto rngSystem = std::make_shared<RNGService>();
		ServiceLocator::RegisterService<IRNGService>(rngSystem);

		int iterCount = 10000;
		int bool5050TrueCount = 0;
		int boolWeightedTrueCount = 0;
		for (int i = 0; i < iterCount; i++)
		{
			if (ServiceLocator::GetService<IRNGService>()->RandomBool())
				bool5050TrueCount++;
			if (ServiceLocator::GetService<IRNGService>()->WeightedRandomBool(0.2f))
				boolWeightedTrueCount++;
		}
		std::cout << "For the 50/50 bool generator, out of " << iterCount << " iterations, " << bool5050TrueCount << " were true.";
		assert(std::abs((float)bool5050TrueCount / iterCount - 0.5f) < 0.02f);
		std::cout << "For the weighted bool generator with probability 20%, out of " << iterCount << " iterations, " << boolWeightedTrueCount << " were true.";
		assert(std::abs((float)boolWeightedTrueCount / iterCount - 0.2f) < 0.02f);

		for (int i = 0; i < iterCount; i++)
		{
			int generated = ServiceLocator::GetService<IRNGService>()->RandomInt(3, 10);
			assert(generated <= 10 && generated >= 3);
		}
	}
	catch (int errorNum)
	{
		return errorNum;
	}
}

static void assert(bool _result)
{
	if (!_result)
		throw 1;
}