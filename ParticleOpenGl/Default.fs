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
    vec3 Ambient;
    vec3 Diffuse;
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

vec3 CalcPointLight(SLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);

    float distance = length(light.Position - fragPos); 

    vec3 ambient  = light.Ambient  * Material.Ambient;
    vec3 diffuse  = light.Diffuse  * diff * Material.Diffuse;
    vec3 specular = light.Specular * spec * Material.Specular;

    return (ambient + diffuse + specular);
} 


void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 Result;
    for(int i = 0; i < LightArraySize; i++)
        Result += CalcPointLight(LightArray[i], norm, FragPos, viewDir);

    FragOutColor = vec4(Result, 1);
} 


//void main()
//{
    //Ambient
    //vec3 Ambient = Light.Ambient * vec3(texture(Material.Diffuse, TexCoords));
  //  vec3 Ambient = Light.Ambient * Material.Diffuse;
    // diffuse 
    //vec3 Norm = normalize(Normal);
    //vec3 LightDir = normalize(Light.Position - FragPos);
    //float Diff = max(dot(Norm, LightDir), 0.0);
    //vec3 Diffuse = Light.Diffuse * Diff * vec3(texture(Material.Diffuse, TexCoords));
   // vec3 Diffuse = Light.Diffuse * Diff * Material.Diffuse;
    // specular
    //vec3 ViewDir = normalize(ViewPos - FragPos);
    //vec3 ReflectDir = reflect(-LightDir, Norm);  
    //float Spec = pow(max(dot(ViewDir, ReflectDir), 0.0), 32);
    //vec3 Specular = Light.Specular * (Material.Specular * Spec);  
        
    //vec3 Result = (Ambient + Diffuse + Specular) * ObjectColor;
    //FragOutColor = vec4(Result, 1.0);
//} 
