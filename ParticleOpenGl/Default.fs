#version 330 core
out vec4 FragOutColor;

in vec3 FragInColor;

void main()
{
    FragOutColor = vec4(FragInColor, 1.0);
}