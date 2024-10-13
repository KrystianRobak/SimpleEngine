#version 330 core

#define LightArraySize 1


out vec4 FragOutColor;

struct SLight
{
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct SMaterial
{
    sampler2D Diffuse;

    vec3 Specular;
    float Shininess;
};

in vec2 TexCoords;

in vec3 Normal;
in vec3 FragPos;

uniform SLight Light;
uniform SMaterial Material;

uniform vec3 ViewPos; 
uniform vec3 ObjectColor;

uniform SLight LightArray[LightArraySize];

void main()
{
    //Ambient
    vec3 Ambient = Light.Ambient * vec3(texture(Material.Diffuse, TexCoords));

    // diffuse 
    vec3 Norm = normalize(Normal);
    vec3 LightDir = normalize(Light.Position - FragPos);
    float Diff = max(dot(Norm, LightDir), 0.0);
    vec3 Diffuse = Light.Diffuse * Diff * vec3(texture(Material.Diffuse, TexCoords));
    
    // specular
    vec3 ViewDir = normalize(ViewPos - FragPos);
    vec3 ReflectDir = reflect(-LightDir, Norm);  
    float Spec = pow(max(dot(ViewDir, ReflectDir), 0.0), 32);
    vec3 Specular = Light.Specular * (Material.Specular * Spec);  
        
    vec3 Result = (Ambient + Diffuse + Specular) * ObjectColor;
    FragOutColor = vec4(Result, 1.0);
} 