#include "SystemInitializer.h"
#include <libloaderapi.h>
#include <iostream>



bool SystemInitializer::InitializeSystem(const std::string& dllPath)
{
    HMODULE hDll = LoadLibraryA(dllPath.c_str());
    if (!hDll)
    {
        std::cerr << "Failed to load DLL: " << dllPath << std::endl;
        return false;
    }

    // Get the factory functions
    SystemInterface* (*CreateSystemFunc)() = (SystemInterface * (*)())GetProcAddress(hDll, "CreatePlugin");
    void (*DestroySystemFunc)(SystemInterface*) = (void (*)(SystemInterface*))GetProcAddress(hDll, "DestroyPlugin");

    if (!CreateSystemFunc || !DestroySystemFunc)
    {
        std::cerr << "Failed to get factory functions from DLL: " << dllPath << std::endl;
        FreeLibrary(hDll);
        return false;
    }

    // Create a plugin instance
    SystemInterface* System = CreateSystemFunc();
    if (!System)
    {
        std::cerr << "Failed to create plugin instance from DLL: " << dllPath << std::endl;
        FreeLibrary(hDll);
        return false;
    }

    // Initialize the plugin
    if (!System->Initialize())
    {
        std::cerr << "Failed to initialize plugin from DLL: " << dllPath << std::endl;
        DestroySystemFunc(System);
        FreeLibrary(hDll);
        return false;
    }

    // Store the plugin instance
    SystemInstance instance;
    instance.dllHandle = hDll;
    instance.System = System;
    instance.CreateSystem = CreateSystemFunc;
    instance.DestroySystem = DestroySystemFunc;

    Systems.push_back(instance);

    std::cout << "Loaded and initialized plugin: " << System->GetName() << std::endl;
    return true;
}

void SystemInitializer::ExecuteSystems(float dt)
{
    for (auto& instance : Systems)
    {
        if (instance.System)
        {
            instance.System->Execute(dt);
        }
    }
}

void SystemInitializer::DestroyPlugins()
{
    for (auto& instance : Systems)
    {
        if (instance.System)
        {
            instance.System->Cleanup();
            instance.DestroySystem(instance.System);
        }
        if (instance.dllHandle)
        {
            FreeLibrary(instance.dllHandle);
        }
    }
    Systems.clear();
}
