#include "UiSystem.h"

UiSystem::UiSystem()
{
}

UiSystem::~UiSystem()
{
}

bool UiSystem::Initialize()
{
	return false;
}

void UiSystem::Execute()
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