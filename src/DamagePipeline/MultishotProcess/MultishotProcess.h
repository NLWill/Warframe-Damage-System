#pragma once
#include "src/DamagePipeline/FireInstance.h"

class MultishotProcess
{
public:
	static void EvaluateMultishotMods(shared_ptr<FireInstance> fireInstance);
	static int RollForMultishot(shared_ptr<FireInstance> fireInstance);
};