#pragma once
#include "Types.h"
#include "Event.h"

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(const Entity& entity, Event event) = 0;
};


