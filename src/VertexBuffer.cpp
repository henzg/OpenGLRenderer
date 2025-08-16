#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
   : m_BufferType(GL_ARRAY_BUFFER), m_DrawType(GL_STATIC_DRAW)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(m_BufferType, m_RendererID);
    glBufferData(m_BufferType, size, data, m_DrawType);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(m_BufferType, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(m_BufferType, 0);
}
