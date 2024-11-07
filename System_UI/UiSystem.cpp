#define SYSTEMINTERFACE_EXPORTS
#include "UiSystem.h"

UiSystem::UiSystem()
{
}

UiSystem::~UiSystem()
{
}

bool UiSystem::Initialize()
{
	return true;
}

void UiSystem::Execute(float dt)
{
}

void UiSystem::Cleanup()
{
}

std::string UiSystem::GetName() const
{
	return std::string();
}

extern "C" {

    SYSTEMINTERFACE_API SystemInterface* CreatePlugin()
    {
        return new UiSystem();
    }

    SYSTEMINTERFACE_API void DestroyPlugin(SystemInterface* System)
    {
        delete System;
    }

}