#include "Texture.h"
#include "stb_image.h"
#include <iostream>


Texture::Texture()
{
    glGenTextures(1, &m_RendererID);
    glBindTexture(m_TextureType, m_RendererID);
    
    glTexParameteri(m_TextureType, m_TextureWrapS, m_TextureWrapType);
    glTexParameteri(m_TextureType, m_TextureWrapT, m_TextureWrapType);
    glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, m_FilterType);
glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, m_FilterType);
}

void Texture::LoadFromFile(const std::string& filepath, bool hasRGBA, bool flipVerticallyOnLoad)
{
    int w, h, nrChannels;
    if (flipVerticallyOnLoad)
        stbi_set_flip_vertically_on_load(true);

    const char* cFilePath = filepath.c_str(); 
    
    unsigned char* textureData = stbi_load(cFilePath, &w, &h, &nrChannels, 0);
    if (textureData)
    {
        if (!hasRGBA)
            glTexImage2D(m_TextureType, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        else
            glTexImage2D(m_TextureType, 0, GL_RGBA, w, h ,0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "IMAGE::LOAD::SUCCESS::TEXTURE\n";
    }
    else 
    {
        std::cout << "IMAGE::LOAD::FAILED::TEXTURE\n";
    }
    stbi_image_free(textureData);

}

void Texture::Bind()
{
    glBindTexture(m_TextureType, m_RendererID);
}

void Texture::BindandActivate(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    Bind();
}
