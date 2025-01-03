#include "src/Services/RNG/RNGService.h"
#include "src/Services/ServiceLocator.h"
#include<iostream>

int main(){
	try{
ServiceLocator::Initialise();

	assert(ServiceLocator::GetRNG().RandomInt() == 0, 1);

	RNGService properService = RNGService();
	ServiceLocator::Provide(&properService);

		int iterCount = 10000;
		int bool5050TrueCount = 0;
		int boolWeightedTrueCount = 0;
		for (int i = 0; i < iterCount; i++){
			if (ServiceLocator::GetRNG().RandomBool()) bool5050TrueCount++;
			if (ServiceLocator::GetRNG().WeightedRandomBool(0.2f)) boolWeightedTrueCount++;
		}
		std::cout << "For the 50/50 bool generator, out of " << iterCount << " iterations, " << bool5050TrueCount << " were true.";
		std::cout << "For the weighted bool generator with probability 20%, out of " << iterCount << " iterations, " << boolWeightedTrueCount << " were true.";
		
		for (int i = 0; i < iterCount; i++)
		{
			int generated = ServiceLocator::GetRNG().RandomInt(3,10);
			assert(generated <= 10 && generated >= 3, 2);
		}
		
	}
	catch (int errorNum){
		return errorNum;
	}
}

void assert(bool _result, int _errCode){
	if (!_result) 
		throw _errCode;
}