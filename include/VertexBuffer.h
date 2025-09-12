#pragma once

#include "glad/glad.h"
#include "VertexBufferLayout.h"

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    bool IsValid() const {return m_RendererID != 0;}

    virtual const VertexBufferLayout& GetLayout() const {return m_Layout;}
    virtual void SetLayout(const VertexBufferLayout& layout) {m_Layout = layout;}

private:
    unsigned int m_RendererID;
    GLenum m_BufferType, m_DrawType;
    VertexBufferLayout m_Layout;
};
