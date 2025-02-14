#pragma once
#include <vector>
#include <string>
#include "src/WeaponsReworked/FiringModeImpl/FireBehaviour.h"
#include "src/WeaponsReworked/FiringModeImpl/ImpactBehaviour.h"
#include "src/WeaponsReworked/FiringModeImpl/StateBehaviour.h"

class FiringMode
{
public:
	FireBehaviour *firingBehaviour;
	ImpactBehaviour *impactBehaviour;
	StateBehaviour *stateBehaviour;

private:
};
