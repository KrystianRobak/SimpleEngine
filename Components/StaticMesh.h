#pragma once

//#include "Shader.h"
#include "Mesh.h"

//#include <assimp/scene.h>
//#include <assimp/Importer.hpp>
//#include <assimp/postprocess.h>

struct StaticMesh
{
public:
    StaticMesh(bool gamma = false) : gammaCorrection(gamma)
    {
        
    }
    //void Draw(Shader& shader);

    //std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    //void loadModel(std::string const& path);
    //void processNode(aiNode* node, const aiScene* scene);
    //Mesh processMesh(aiMesh* mesh, const aiScene* scene);

private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;
};

