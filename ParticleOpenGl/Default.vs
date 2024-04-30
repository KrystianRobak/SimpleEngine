#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragInColor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    FragInColor = vec3((aPos + 0.5) * 0.5); // Convert vertex position to color range [0,1]
}