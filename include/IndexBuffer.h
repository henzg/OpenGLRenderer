#pragma once

#include "Core.h"

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    GLenum m_BufferType;

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
    bool IsValid() const; // Added IsValid() declaration
};
