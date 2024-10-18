#pragma once

#include "LibExporter.h"

#include <glm.hpp>

struct COMPONENTS_API Renderable
{
	glm::vec3 color;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    float Shininess;
};
