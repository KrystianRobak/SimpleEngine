#pragma once

#include "SystemInterface.h"

class PhysicsSystem : public SystemInterface
{
public:
	void Init();

	void Update(float dt);
};
