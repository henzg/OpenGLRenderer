#include "Mesh.h"

#include "VertexBufferLayout.h"


static const float s_FullCubeVertices[8*36] = 
{
    // pos[0:2] normal[3:5] tex[6:7]
    // front - back - left - right - top - bottom
    -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,  
     0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 0.f, 
     0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 1.f, 1.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,

    -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f, 0.f, 0.f,
     0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f, 1.f, 0.f,
     0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f, 0.f, 1.f,
    -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f, 0.f, 0.f,

    -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f, 0.f, 1.f,
    -0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 1.f, 0.f,
    -0.5f, -0.5f,  0.5f, -1.f, 0.f, 0.f, 0.f, 0.f,
    -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f, 0.f, 1.f,

     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f, 1.f, 1.f,  
     0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 0.f, 1.f,
     0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 0.f, 0.f,
     0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 0.f, 0.f,
     0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f, 1.f, 0.f,
     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f, 1.f, 1.f,

    -0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 0.f, 1.f,
     0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 1.f, 0.f,
     0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 1.f, 0.f,
    -0.5f, -0.5f,  0.5f,  0.f,-1.f, 0.f, 0.f, 0.f,
    -0.5f, -0.5f, -0.5f,  0.f,-1.f, 0.f, 0.f, 1.f,

    -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.f,
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 1.f, 0.f,
     0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 1.f, 0.f,
    -0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f, 0.f, 0.f,
    -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.f
};

Mesh::Mesh(const float* vertices, unsigned int numVertices, const unsigned int* indicies,
           unsigned int numIndicies, const VertexBufferLayout& layout)
    : m_IndexCount(numIndicies), m_VertexCount(numVertices)
{
    // create and bind vertex array object as this stores the state on how the vbo data is interpreted
    m_VAO = std::make_unique<VertexArray>();
    m_VAO->Bind();

    // then create the vbo
        m_VBO = std::make_unique<VertexBuffer>(vertices, numVertices * layout.GetStride());

    // then make index/element buffer
    if(numIndicies > 0)
        m_EBO = std::make_unique<IndexBuffer>(indicies, m_IndexCount);

    // link vbo to vao
    m_VAO->AddBuffer(*m_VBO, layout);

    // unbind
    m_VAO->Unbind();
    m_VBO->Unbind();
    if(m_EBO)
        m_EBO->Unbind();
};

Mesh::~Mesh() {}

std::unique_ptr<Mesh> Mesh::CreateCube(CubeFeature features)
{
    // define attributes for one vertex
    const unsigned int POS_OFFSET = 0;
    const unsigned int NORMAL_OFFSET = 3;
    const unsigned int TEXTCOORD_OFFSET = 6;
    const unsigned int VERTEX_STRIDE_FULL = 8;

    if(!(features & CubeFeature::Position)) {
        std::cerr << "ERROR||CUBE||NO POSITION DATA||\n";
        return nullptr;
    }

    
    std::vector<VertexBufferElement> elements;
    if(features & CubeFeature::Position)
        elements.push_back({ShaderDataType::Float3, "aPos"});
    if(features & CubeFeature::Normal)
        elements.push_back({ShaderDataType::Float3, "aNormal"});
    if(features & CubeFeature::TexCoord)
        elements.push_back({ShaderDataType::Float2, "aTexCoord"});
    
    VertexBufferLayout layout(elements);
    
    std::vector<float> finalVertices;
    const unsigned int NUM_LOGICAL_CUBE_VERTICES =  (sizeof(s_FullCubeVertices)/ sizeof(float)) / VERTEX_STRIDE_FULL;
    const unsigned int NUM_FLOATS = layout.GetStride() / sizeof(float);
    
    finalVertices.reserve(NUM_LOGICAL_CUBE_VERTICES * NUM_FLOATS);

    for (unsigned int i = 0; i < (sizeof(s_FullCubeVertices) / sizeof(float)) / VERTEX_STRIDE_FULL; ++i) {
        unsigned int currentVertexOffset = i * VERTEX_STRIDE_FULL;
        if(features & CubeFeature::Position) {
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + POS_OFFSET + 0]);
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + POS_OFFSET + 1]);
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + POS_OFFSET + 2]);
        }
        if(features & CubeFeature::Normal) {
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + NORMAL_OFFSET + 0]);
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + NORMAL_OFFSET + 1]);
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + NORMAL_OFFSET + 2]);
        }
        if(features & CubeFeature::TexCoord) {
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + TEXTCOORD_OFFSET + 0]);
            finalVertices.push_back(s_FullCubeVertices[currentVertexOffset + TEXTCOORD_OFFSET + 1]);
        }
    }
        return std::make_unique<Mesh>(finalVertices.data(), NUM_LOGICAL_CUBE_VERTICES, nullptr, 0, layout);
}

void Mesh::Draw(const Renderer& renderer, const glm::mat4& view, const glm::mat4& projection) const
{
    // Assuming the shader is already bound and uniforms are set by the caller
    // If not, you'd need a way to get the active shader and set uniforms here.
    // For now, we'll assume the shader (and model matrix) are handled externally.
    m_VAO->Bind();
    if(m_IndexCount > 0) 
    {
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
    } else if (m_VertexCount > 0)
    {
        glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
    } else {
        std::cerr << "||WARNING||NO VERTICIES OR INDICIES FOR MESH||\n";
    }
    m_VAO->Unbind();
}
