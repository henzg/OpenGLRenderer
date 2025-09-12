#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray 
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    bool IsValid() const { return m_RendererID != 0; }
private:
    unsigned int m_RendererID;
};
