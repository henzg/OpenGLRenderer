#include "Mesh.h"

Mesh::Mesh(const float* verticies, unsigned int numVerticies, const unsigned int* indicies,
           unsigned int numIndicies, const VertexBufferLayout& layout)
    : m_IndexCount(numIndicies)
{
    // create and bind vertex array object as this stores the state on how the vbo data is interpreted
    m_VAO = std::make_unique<VertexArray>();
    m_VAO->Bind();

    // then create the vbo
    m_VBO = std::make_unique<VertexBuffer>(verticies, numVerticies * layout.GetStride());

    // then make index/element buffer
    m_EBO = std::make_unique<IndexBuffer>(indicies, m_IndexCount);

    // link vbo to vao
    m_VAO->AddBuffer(*m_VBO, layout);

    // unbind
    m_VAO->Unbind();
    m_VBO->Unbind();
    m_EBO->Unbind();
};

Mesh::~Mesh() {}

void Mesh::Draw() const
{
    m_VAO->Bind();
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
    m_VAO->Unbind();
}
