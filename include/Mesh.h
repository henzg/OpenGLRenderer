#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Shader.h"

#include <vector>
#include <string>
#include <memory>

#include "GeometryData.h"

enum class MeshLayout
{
    NONE = 0,
    POSITION_ONLY,
    POSITION_NORMAL,
    POSITION_TEXTCOORD,
    POSITION_NORMAL_TEXCOORD,
};

enum class CubeFeature : unsigned int
{
    None = 0,
    Position = 1  << 0,
    Normal = 1 << 1,
    TexCoord = 1 << 2,

    All = Position | Normal | TexCoord
};

inline CubeFeature operator|(CubeFeature a, CubeFeature b) {
    return static_cast<CubeFeature>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline bool operator&(CubeFeature a, CubeFeature b) {
    return (static_cast<unsigned int>(a) & static_cast<unsigned int>(b)) !=0;
}



class Mesh {
private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_EBO;
    
    std::shared_ptr<Shader> m_Shader;
    std::vector<std::shared_ptr<Texture>> m_Textures;

    unsigned int m_IndexCount;
    unsigned int m_VertexCount;

public:
    Mesh(const float* verticies, unsigned int numVerticies, 
         const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout);
    ~Mesh();

    static std::unique_ptr<Mesh>CreateCube(CubeFeature features = CubeFeature::All);

    void Draw() const;

};
