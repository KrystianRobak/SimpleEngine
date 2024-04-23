#pragma once
#include <../glm.hpp>

struct PointLightComponent {
    bool enabled{ false };
    bool debugRender{ false };

    glm::vec3 ambient{ 0.7f, 0.7f, 0.7f };
    glm::vec3 diffuse{ 0.7f, 0.7f, 0.7f };
    glm::vec3 specular{ 0.7f, 0.7f, 0.7f };
    // distance 50
    float constant{ 1.0f };
    float linear{ 0.09f };
    float quadratic{ 0.032f };
};

struct DirectionalLightComponent {
    bool enabled{ false };
    glm::vec3 direction{ 0.0f, 1.0f, 0.0f };
    glm::vec3 ambient{ 0.4f, 0.4f, 0.4f };
    glm::vec3 diffuse{ 0.4f, 0.4f, 0.4f };
    glm::vec3 specular{ 0.4f, 0.4f, 0.4f };
};

struct SpotLightComponent {
    bool enabled{ false };
    bool flashlightMode{ false }; // follow camera
    bool debugRender{ false };

    glm::vec3 ambient{ 0.4f, 0.4f, 0.4f };
    glm::vec3 diffuse{ 0.4f, 0.4f, 0.4f };
    glm::vec3 specular{ 0.4f, 0.4f, 0.4f };

    float cutOff{ 12.5f };
    float outerCutOff{ 17.5f };
    // distance 50
    float constant{ 1.0f };
    float linear{ 0.09f };
    float quadratic{ 0.032f };
};

