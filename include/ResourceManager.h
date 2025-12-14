#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <string>
#include <memory>
#include <map>
#include <vector>

class ResourceManager
{
private:
    std::map<std::string, std::unique_ptr<VertexArray>> m_VAOs;
    std::map<std::string, std::unique_ptr<VertexBuffer>> m_VBOs;
    std::map<std::string, std::unique_ptr<IndexBuffer>> m_IBOs; // Added IndexBuffer map
    std::map<std::string, std::unique_ptr<Shader>> m_Shaders;
    std::map<std::string, std::unique_ptr<Mesh>> m_Meshes;
    std::map<std::string, std::unique_ptr<Texture>> m_Textures;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    /*--- Vertex Array Manager Functions------------------------------------------------------------*/
    void AddVertexArray(const std::string& name);
    void ClearVertexArrays();
    VertexArray* GetVertexArray(const std::string& name);
    void BindVertexArray(const std::string& name);

    /*--- Vertex Buffer Manager Functions------------------------------------------------------------*/
    void AddVertexBuffer(const std::string& name, const void* data, unsigned int size);
    VertexBuffer* GetVertexBuffer(const std::string& name);
    void ClearVertexBuffers();

    /*--- Index Buffer Manager Functions------------------------------------------------------------*/
    void AddIndexBuffer(const std::string& name, const unsigned int* data, unsigned int count);
    IndexBuffer* GetIndexBuffer(const std::string& name);
    void ClearIndexBuffers();

    /*--- Mesh Manager Functions------------------------------------------------------------*/
    void AddMesh(const std::string& name, const float* verticies, unsigned int numVerticies, 
                 const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout);
    void AddMesh(const std::string& name, std::unique_ptr<Mesh> mesh);
    const Mesh* GetMesh(const std::string& name);
    void ClearMeshes();

    /*-- Shader Manger Functions------------------------------------------------------------*/
    void AddShader(const std::string& name, const std::string& vsPath, const std::string& fsPath);
    Shader* GetShader(const std::string& name);
    void ClearShaders();
    
    /*--- Texture Manger Functions ---------------------------------------------------------*/
    void AddTexture(const std::string& name, const std::string& filePath, bool flip_on_load, bool hasRGBA);
    Texture* GetTexture(const std::string& name);
    void ClearTextures();
};