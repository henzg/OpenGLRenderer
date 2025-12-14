#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count), m_BufferType(GL_ELEMENT_ARRAY_BUFFER)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(m_BufferType, m_RendererID);
    glBufferData(m_BufferType, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(m_BufferType, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(m_BufferType, 0);
}

bool IndexBuffer::IsValid() const
{
    return m_RendererID != 0;
}
