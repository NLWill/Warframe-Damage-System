#include "../src/Services/RNG/RNGService.h"
#include "../src/Services/ServiceLocator.h"
#include <iostream>

static void assert(bool _result, int _errorCode);

int main()
{
	try
	{
		ServiceLocator::Initialise();

		assert(ServiceLocator::GetRNG().RandomInt() == 0, 1);

		auto rngSystem = make_shared<RNGService>();
		ServiceLocator::Provide(rngSystem);

		int iterCount = 10000;
		int bool5050TrueCount = 0;
		int boolWeightedTrueCount = 0;
		for (int i = 0; i < iterCount; i++)
		{
			if (ServiceLocator::GetRNG().RandomBool())
				bool5050TrueCount++;
			if (ServiceLocator::GetRNG().WeightedRandomBool(0.2f))
				boolWeightedTrueCount++;
		}
		std::cout << "For the 50/50 bool generator, out of " << iterCount << " iterations, " << bool5050TrueCount << " were true.";
		assert(std::abs((float)bool5050TrueCount / iterCount - 0.5f) < 0.02f, 2);
		std::cout << "For the weighted bool generator with probability 20%, out of " << iterCount << " iterations, " << boolWeightedTrueCount << " were true.";
		assert(std::abs((float)boolWeightedTrueCount / iterCount - 0.2f) < 0.02f, 3);

		for (int i = 0; i < iterCount; i++)
		{
			int generated = ServiceLocator::GetRNG().RandomInt(3, 10);
			assert(generated <= 10 && generated >= 3, 4);
		}
	}
	catch (int errorNum)
	{
		return errorNum;
	}
}

static void assert(bool _result, int _errCode)
{
	if (!_result)
		throw _errCode;
}