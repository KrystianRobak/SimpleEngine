#pragma once

#include "LibExporter.h"

#include <glm.hpp>
#include <string>

struct COMPONENTS_API Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};