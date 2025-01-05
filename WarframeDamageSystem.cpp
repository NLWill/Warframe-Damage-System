#include <iostream>
#include <string>
#include "src/Services/Logging/LogService.h"
#include "src/Services/RNG/RNGService.h"
#include "src/Services/ServiceLocator.h"

int main()
{
	std::cout << "Hello, World!" << std::endl;
	std::string inp;

	ServiceLocator::Initialise();
	auto logSystem = new LogService();
	ServiceLocator::Provide(logSystem);
	auto rngSystem = new RNGService();
	ServiceLocator::Provide(rngSystem);

	int sum = 0;
	for (int i = 0; i < 100000; i++)
	{
		int gen = ServiceLocator::GetRNG().RandomInt(10);
		sum += gen;
	}
	ServiceLocator::GetLogger().LogWarning(std::to_string(sum));
	std::string average = "Average was " + std::to_string((float)sum / 100000);
	ServiceLocator::GetLogger().LogError(average);
	
	//std::cin >> inp;
};