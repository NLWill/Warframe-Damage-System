#pragma once
#include "src/DamagePipeline/FireInstance.h"

class MultishotProcess
{
public:
	static void EvaluateMultishotMods(std::shared_ptr<FireInstance> fireInstance);
	static int RollForMultishot(std::shared_ptr<FireInstance> fireInstance);
};