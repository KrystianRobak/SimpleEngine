#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 FragInColor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec4 Color;

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    FragInColor = Color;
}