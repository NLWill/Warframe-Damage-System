#pragma once
#include "src/DamagePipeline/FireInstance.h"

class MultishotProcess
{
public:
	static void EvaluateMultishotMods(FireInstance *fireInstance);
	static int RollForMultishot(FireInstance *fireInstance);
};