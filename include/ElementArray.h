#pragma once

#include "glad/glad.h"

class ElementArray
{
public:
    ElementArray(const unsigned int* data, unsigned int count);
    ~ElementArray();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
private:
    unsigned int m_RendererID;
    GLenum m_BufferType;
    unsigned int m_Count;
};
