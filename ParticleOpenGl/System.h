#pragma once
#include <set>
#include "Coordinator.h"

class System
{
public:
	virtual void Update(float dt) = 0;
	void Bind(Coordinator& coordinator)
	{
		coordinatorPtr = std::make_shared<Coordinator>(coordinator);
	};
public:
	std::set<Entity> mEntities;
	std::shared_ptr<Coordinator> coordinatorPtr;
};

