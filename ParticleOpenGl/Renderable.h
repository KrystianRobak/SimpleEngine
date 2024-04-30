#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm.hpp>

struct Renderable
{
	glm::vec4 color;

    void GenerateGUIElements(std::uint32_t entity)
    {
        std::string label = "Object##" + entity;
        if (ImGui::CollapsingHeader(label.c_str()))
        {
            label = "Color##" + entity;
            ImGui::ColorPicker4(label.c_str(), &color[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        }
    }
};
