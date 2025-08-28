#pragma once

#include <cstdint>
#include <string>
#include "glad/glad.h"

class Texture {    

public:
    Texture();
    ~Texture() = default;

    void LoadFromFile(const std::string& filepath, bool hasRGBA = false, bool flipVerticallyOnLoad = true);
    void Bind();
    void BindandActivate(GLenum textureUnit);


private:
    std::uint32_t m_RendererID;
    GLenum m_TextureType    = GL_TEXTURE_2D;
    GLenum m_TextureWrapS   = GL_TEXTURE_WRAP_S;
    GLenum m_TextureWrapT   = GL_TEXTURE_WRAP_T;
    GLint m_TextureWrapType = GL_REPEAT;
    GLint m_FilterType      = GL_LINEAR;



};
