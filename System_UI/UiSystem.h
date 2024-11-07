#pragma once
#include "SystemInterface.h"

class UiSystem : public SystemInterface
{
public:
	UiSystem();
	virtual ~UiSystem();

	virtual bool Initialize() override;
	virtual void Execute(float dt) override;
	virtual void Cleanup() override;
	virtual std::string GetName() const override;

private:
};
