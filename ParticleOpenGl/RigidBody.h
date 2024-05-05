#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glm.hpp>

struct RigidBody
{
	glm::vec3 velocity;
	glm::vec3 acceleration;

    void GenerateGUIElements(std::uint32_t entity)
    {
        std::string label = "Object##" + entity;

            label = "Velocity## " + entity;
            ImGui::SliderFloat3(label.c_str(), &velocity[0], -15.f, 15.f);
            label = "Acceleration## " + entity;
            ImGui::SliderFloat3(label.c_str(), &acceleration[0], -15.f, 15.f);

    }
};
