#pragma once

#ifdef SYSTEMINTERFACE_EXPORTS
#define SYSTEMINTERFACE_API __declspec(dllexport)
#else
#define SYSTEMINTERFACE_API __declspec(dllimport)
#endif

#include "Types.h"
#include <set>

class SYSTEMINTERFACE_API SystemInterface
{
protected:
    std::set<Entity> mEntities;

public:

    virtual ~SystemInterface() {}


    virtual bool Initialize() = 0;
    virtual void Execute(float dt) = 0;
    virtual void Cleanup() = 0;

    virtual std::string GetName() const = 0;

	std::set<Entity>& GetEntities()
	{
		return this->mEntities;
	}

};

extern "C" {
    // Factory function to create a plugin instance
    SYSTEMINTERFACE_API SystemInterface* CreateSystem();

    // Factory function to destroy a plugin instance
    SYSTEMINTERFACE_API void DestroySystem(SystemInterface* System);
}
