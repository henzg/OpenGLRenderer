#pragma once

#include "glad/glad.h"

#include <vector>
#include <string>

enum class ShaderDataType
{
    None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float:     return GL_FLOAT;
        case ShaderDataType::Float2:    return GL_FLOAT;
        case ShaderDataType::Float3:    return GL_FLOAT;
        case ShaderDataType::Float4:    return GL_FLOAT;
        case ShaderDataType::Mat3:      return GL_FLOAT;
        case ShaderDataType::Mat4:      return GL_FLOAT;
        case ShaderDataType::Int:       return GL_INT;
        case ShaderDataType::Int2:      return GL_INT;
        case ShaderDataType::Int3:      return GL_INT;
        case ShaderDataType::Int4:      return GL_INT;
        case ShaderDataType::Bool:      return GL_BOOL;
    }
    return 0;
};

struct VertexBufferElement 
{
    std::string Name;
    ShaderDataType Type;
    size_t Size;
    size_t Offset;
    bool Normalized;

    VertexBufferElement() {}

    VertexBufferElement(ShaderDataType type, const std::string& name, bool Normalized = false)
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(false)
    {}

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
        }
        return 0;
    }

    uint32_t GetComponentCount() const
    {
        switch (Type)
        {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::Bool:      return 1;
        }
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride = 0;

private:
    void CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

public:
    VertexBufferLayout() {}
    VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements)
        : m_Elements(elements) 
    {
        CalculateOffsetsAndStride();
    }

    inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    inline uint32_t GetStride() const { return m_Stride; }

    std::vector<VertexBufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<VertexBufferElement>::iterator end() { return m_Elements.end(); }
};


