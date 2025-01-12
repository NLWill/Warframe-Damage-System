#include <iostream>
#include <string>
#include "src/Services/Logging/LogService.h"
#include "src/Services/RNG/RNGService.h"
#include "src/Services/ServiceLocator.h"

#include "src/Mods/ModEffects/ProbabilityModEffectWrapper.h"
#include "src/Mods/ModEffects/ModEffect.h"
#include <cmath>

#include "src/Weapons/WeaponFactory.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Target/Target.h"

int main()
{

	ServiceLocator::Initialise();
	auto logSystem = new LogService();
	ServiceLocator::Provide(logSystem);
	auto rngSystem = new RNGService();
	ServiceLocator::Provide(rngSystem);

	std::cout << "Hello, World!" << std::endl;
	std::string inp;

	int sum = 0;
	for (int i = 0; i < 100000; i++)
	{
		int gen = ServiceLocator::GetRNG().RandomInt(10);
		sum += gen;
	}
	ServiceLocator::GetLogger().LogWarning(std::to_string(sum));
	std::string average = "Average was " + std::to_string((float)sum / 100000);
	ServiceLocator::GetLogger().LogError(average);

	Weapon *ax52 = WeaponFactory::GetAX52();
	Target *target = new Target();

	do
	{
		std::cout << "Testing the damage pipeline" << std::endl;
		std::cout << DamagePipeline::RunDamagePipeline(*ax52, "Normal Attack", *target, "Body") << std::endl;
		std::cin >> inp;
	} while (inp == "y" || inp == "Y");

	// std::cin >> inp;
	delete ax52;
	delete target;
};