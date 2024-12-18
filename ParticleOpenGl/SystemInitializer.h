#pragma once

#include "SystemInterface.h"
#include <vector>
#include <windows.h>

struct SystemInstance
{
	HMODULE dllHandle;
	SystemInterface* System;
	SystemInterface* (*CreateSystem)();
	void (*DestroySystem)(SystemInterface*);
};

class SystemInitializer
{
public:
	SystemInitializer() {};
	~SystemInitializer() {};

	bool InitializeSystem(const std::string& dllPath);

	void ExecuteSystems(float dt);

	void DestroyPlugins();

private:
	std::vector<SystemInstance> Systems;

};

