#pragma once
#include "src/DamagePipeline/DamageInstance.h"
#include "src/DamagePipeline/FireInstance.h"

class StatusChanceProcess
{
public:
	static void EvaluateStatusChanceMods(FireInstance *fireInstance);
	static void EvaluateStatusDamageMods(FireInstance *fireInstance);
	static void RollForStatus(FireInstance *fireInstance);

private:
};