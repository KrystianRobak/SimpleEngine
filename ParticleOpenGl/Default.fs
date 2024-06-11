#version 330 core
out vec4 FragOutColor;

in vec4 FragInColor;

void main()
{
    FragOutColor = FragInColor;
}