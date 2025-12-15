#include "ResourceManager.h"
#include <iostream>

void ResourceManager::Reset()
{
    // Clear in a predictable order
    ClearTextures();
    ClearMeshes();
    ClearShaders();
    ClearIndexBuffers();
    ClearVertexBuffers();
    ClearVertexArrays();
}

/*--- Vertex Array Manager Functions------------------------------------------------------------*/
void ResourceManager::AddVertexArray(const std::string& name) {
    m_VAOs.emplace(name, std::make_unique<VertexArray>());
}

void ResourceManager::ClearVertexArrays() {
    m_VAOs.clear();
}

VertexArray* ResourceManager::GetVertexArray(const std::string& name) {
    auto it = m_VAOs.find(name);
    if(it != m_VAOs.end()) {
        if(it->second->IsValid())
            return it->second.get(); 
    }
    std::cerr << "ERROR||COULD NOT FIND VAO||" << name << "||\n";
    return nullptr;
}

void ResourceManager::BindVertexArray(const std::string& name) {
    VertexArray* vao = GetVertexArray(name);
    if(vao)
        vao->Bind();
}

/*--- Vertex Buffer Manager Functions------------------------------------------------------------*/
void ResourceManager::AddVertexBuffer(const std::string& name, const void* data, unsigned int size) {
    m_VBOs.emplace(name, std::make_unique<VertexBuffer>(data, size));
}

void ResourceManager::ClearVertexBuffers() {
    m_VBOs.clear();
}

/*--- Index Buffer Manager Functions------------------------------------------------------------*/
void ResourceManager::AddIndexBuffer(const std::string& name, const unsigned int* data, unsigned int count) {
    m_IBOs.emplace(name, std::make_unique<IndexBuffer>(data, count));
}

IndexBuffer* ResourceManager::GetIndexBuffer(const std::string& name) {
    auto it = m_IBOs.find(name);
    if(it != m_IBOs.end()) {
        if(it->second->IsValid())
            return it->second.get();
    }
    std::cerr << "ERROR||COULD NOT FIND IBO||"<< name << "||\n";
    return nullptr;
}

void ResourceManager::ClearIndexBuffers() {
    m_IBOs.clear();
}

VertexBuffer* ResourceManager::GetVertexBuffer(const std::string& name) {
    auto it = m_VBOs.find(name);
    if(it != m_VBOs.end()) {
        if(it->second->IsValid())
            return it->second.get();
    }
    std::cerr << "ERROR||COULD NOT FIND VBO||"<< name << "||\n";
    return nullptr;
}

/*--- Mesh Manager Functions------------------------------------------------------------*/
void ResourceManager::AddMesh(const std::string& name, const float* verticies, unsigned int numVerticies, 
                 const unsigned int* indicies, unsigned int numIndicies, const VertexBufferLayout& layout) {
    m_Meshes.emplace(name, std::make_unique<Mesh>(verticies, numVerticies, indicies, numIndicies, layout));
}

void ResourceManager::AddMesh(const std::string& name, std::unique_ptr<Mesh> mesh) {
    m_Meshes.emplace(name, std::move(mesh));
}

const Mesh* ResourceManager::GetMesh(const std::string& name) {
    auto it = m_Meshes.find(name);
    if(it!= m_Meshes.end()) {
        return it->second.get();
    }
    std::cerr << "ERROR||MESH||COULD NOT FIND MESH||" << name << "||\n";
    return nullptr;
}

void ResourceManager::ClearMeshes() {
    m_Meshes.clear();
}

/*-- Shader Manger Functions------------------------------------------------------------*/
void ResourceManager::AddShader(const std::string& name, const std::string& vsPath, const std::string& fsPath) {
    m_Shaders.emplace(name, std::make_unique<Shader>(vsPath.c_str(), fsPath.c_str()));
}

Shader* ResourceManager::GetShader(const std::string& name) {
    auto it = m_Shaders.find(name);
    if (it != m_Shaders.end())
        if (it->second->IsValid())
            return it->second.get();
    std::cout << "ERROR||FIND||SHADER||" << name << "||NOT FOUND||\n";
    return nullptr;
}

void ResourceManager::ClearShaders() {
    m_Shaders.clear();
}

/*--- Texture Manger Functions ---------------------------------------------------------*/
void ResourceManager::AddTexture(const std::string& name, const std::string& filePath, bool flip_on_load, bool hasAlpha) {
    std::unique_ptr<Texture> newTexture = std::make_unique<Texture>();
    newTexture->LoadFromFile(filePath, flip_on_load, hasAlpha);
    m_Textures.emplace(name, std::move(newTexture));
}

Texture* ResourceManager::GetTexture(const std::string& name) {
    auto it = m_Textures.find(name);
    if (it != m_Textures.end())
        return it->second.get();
    std::cout << "ERROR||FIND||TEXTURE||" << name << "||NOT FOUND||\n";
    return nullptr;
}

Texture* ResourceManager::GetTexture(const std::string& name) const {
    auto it = m_Textures.find(name);
    if (it != m_Textures.end())
        return it->second.get();
    std::cout << "ERROR||FIND||TEXTURE||" << name << "||NOT FOUND||\n";
    return nullptr;
}

void ResourceManager::ClearTextures() {
    m_Textures.clear();
}
