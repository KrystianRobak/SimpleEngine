#pragma once
#include "LibExporter.h" 
#include <glm.hpp>

enum class COMPONENTS_API LightType {
    Directional,
    Point,
    Spot
};

struct COMPONENTS_API LightSource {
    LightType type;
    glm::vec3 color;
    float intensity;

    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;

    // Additional properties like attenuation for point lights
    float constant;
    float linear;
    float quadratic;
    // For spotlights
    float cutOff;
    float outerCutOff;
};