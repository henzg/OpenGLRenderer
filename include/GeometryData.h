#pragma once

#include <vector>
#include "glm/glm.hpp"

struct Vertex3D 
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoords;

    Vertex3D(const glm::vec3& pos, const glm::vec3& norm = glm::vec3(0.f,0.f,0.f), const glm::vec2& texCoords = glm::vec2(0,0))
        : position(pos), normal(norm), textureCoords(texCoords) {}
};

struct Vertex3D_PosOnly
{
    glm::vec3 position;

    Vertex3D_PosOnly(const glm::vec3& pos) 
        : position(pos) {}
};

struct Vertex3D_PosText
{
    glm::vec3 position;
    glm::vec2 textureCoords;

    Vertex3D_PosText(const glm::vec3& pos, const glm::vec2& texCoords = glm::vec2(0,0))
        : position(pos), textureCoords(texCoords) {}
};

struct Vertex3D_PosNormal 
{
    glm::vec3 position;
    glm::vec3 normal;

    Vertex3D_PosNormal(const glm::vec3& pos, const glm::vec3& norm = glm::vec3(0.f,0.f,0.f))
        : position(pos), normal(norm) {}
};



