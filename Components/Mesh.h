    #pragma once

    #include "LibExporter.h"

    #include <glm.hpp>
    #include <vector>

    //#include <gtc/matrix_transform.hpp>
    //#include "Shader.h"

    #define MAX_BONE_INFLUENCE 4

    struct COMPONENTS_API Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

  struct COMPONENTS_API Texture {
        unsigned int id;
        char* type;
        char* path;
    };

    struct COMPONENTS_API Mesh
    {
    public:

        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        //void Draw(Shader& shader);
    private:
        unsigned int VAO, VBO, EBO;

        //void setupMesh();
    };