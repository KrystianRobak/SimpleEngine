#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glm.hpp>

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

    void GenerateGUIElements(std::uint32_t entity)
    {
        std::string label = "Transform##" + entity;
        ImGui::Text(label.c_str());
        //if (ImGui::CollapsingHeader(label.c_str()))
        //{
            label = "Position## " + entity;
            ImGui::SliderFloat3(label.c_str(), &position[0], -30.f, 30.f);
            label = "Rotation## " + entity;
            ImGui::SliderFloat3(label.c_str(), &rotation[0], 0.f, 1.f);
            label = "Scale## " + entity;
            ImGui::SliderFloat3(label.c_str(), &scale[0] , -15.f, 15.f);
        //}
    }
};