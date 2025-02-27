#include "../src/Mods/ModEffects/ProbabilityModEffectWrapper.h"
#include "../src/Mods/ModEffects/ConstantModEffect.h"
#include "../src/Services/ServiceLocator.h"
#include "../src/Services/RNG/RNGService.h"
#include<iostream>
#include<cmath>
#include<string>

static void assert(bool _result, int _errorCode);

int main(){
	ServiceLocator::Initialise();
	ServiceLocator::Provide(new RNGService());
	try{
		ConstantModEffect valueOne = ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 1);
		std::cout << "ValueOne ConstantModEffect created" << std::endl;

		if (valueOne.GetModValue(nullptr) != 1){
			return EXIT_FAILURE;
		}

		float successProbability = 0.8f;
		ProbabilityModEffect probWrapper = ProbabilityModEffect(valueOne, successProbability);

		//std::cout << "ProbabilityModEffectWrapper created" << std::endl;

		int successCount = 0000;
		int iterationCount = 10000;
		for (int i = 0; i < iterationCount; i++)
		{
			successCount += probWrapper.GetModValue(nullptr);
		}
		
		float proportionCorrect = (float)successCount / iterationCount;
		std::string msg = "Proportion correct for ProbabilityModEffect = " + std::to_string(proportionCorrect);
		std::cout << msg << std::endl;
		float deviationFromInputProbability = std::abs(proportionCorrect - successProbability);

		if (deviationFromInputProbability > 0.02f){
			throw 1;
		}
	}
	catch (int errorNum){
		return errorNum;
	}

	return EXIT_SUCCESS;
}

static void assert(bool _result, int _errCode)
{
	if (!_result)
		throw _errCode;
}