#pragma once
#include <string>
#include <vector>

std::vector<std::string> InitComponents =
{
"Components.dll"
};

std::vector<std::string> ComponentsUsed =
{
"Gravity",
"RigidBody",
"Renderable",
"Thrust",
"Transform",
"Collision",
"Camera",
"Player",
"Thrust",
"LightSource"
};

std::vector<std::string> InitSystems =
{
"Systems/CameraControl.dll",
"Systems/Physics.dll",
"Systems/Renderer.dll",
"Systems/UI.dll"
};