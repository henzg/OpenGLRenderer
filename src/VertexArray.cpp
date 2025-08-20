#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include <iostream>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    for (GLuint i = 0;i<elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, 
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type), 
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              static_cast<GLsizei>(layout.GetStride()),
                              reinterpret_cast<const void*>( static_cast<uintptr_t>(element.Offset)));
        std::cout << "Element info: || elementcomponentcount: " << element.GetComponentCount() << " || Normalized: " << element.Normalized << " || Stride " << layout.GetStride() << " || offset: " << element.Offset << "\n";
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
