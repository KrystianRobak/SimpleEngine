#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glm.hpp>

struct RigidBody
{
    float mass;
	glm::vec3 velocity;
	glm::vec3 acceleration;
    glm::vec3 momentum;

    void GenerateGUIElements(std::uint32_t entity)
    {
        std::string label = "Object##" + entity;

            label = "Velocity## " + entity;
            ImGui::SliderFloat3(label.c_str(), &velocity[0], -50.f, 50.f);
            label = "Acceleration## " + entity;
            ImGui::SliderFloat3(label.c_str(), &acceleration[0], -15.f, 15.f);

    }
};
