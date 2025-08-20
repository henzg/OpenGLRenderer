#include "ElementArray.h"

ElementArray::ElementArray(const unsigned int* data, unsigned int count)
    : m_BufferType(GL_ELEMENT_ARRAY_BUFFER), m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(m_BufferType, m_RendererID);
    glBufferData(m_BufferType, sizeof(unsigned int) * count, data, GL_STATIC_DRAW);

}

ElementArray::~ElementArray()
{
    glDeleteBuffers(1, &m_RendererID);
}

void ElementArray::Bind() const
{
    glBindBuffer(m_BufferType, m_RendererID);
}

void ElementArray::Unbind() const
{
    glBindBuffer(m_BufferType, 0);
}
