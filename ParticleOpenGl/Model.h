#pragma once
#include "Shader.h"
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>



class Model
{
public:
    Model(std::string const& path, std::string name, bool gamma = false) : gammaCorrection(gamma), position{ 0.f, 0.f, 0.f }, axis{1.f, 1.f, 1.f}
    {
        this->model = glm::mat4(1.0f);
        this->angle = 20.f;
        this->name = name;
        loadModel(path);
    }
    void Draw(Shader& shader, glm::mat4 projection, glm::mat4 view);
    glm::mat4 GetModel() { return model; };
    float* GetPosition() { return position; }
    void GenerateGUIElements(int index);

    bool toDelete = false;

private:
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

  

private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;
    glm::mat4 model;
    float color[4];

    bool texture = false;
    bool lightning = false;
    float position[3];
    bool axis[3];
    float angle;
    std::string name;
};

