#pragma once

#include "SystemInterface.h"

class PhysicsSystem : public SystemInterface
{
public:
	virtual bool Initialize() override;
	virtual void Execute(float dt) override;
	virtual void Cleanup() override;

	virtual std::string GetName() const override;
};
