#pragma once

#include "Camera.h"
#include <vector>
#include <functional>
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

class Renderer;
class Shader;
class Mesh;

class Scene
{
public:
    // Option B: simple entity with Transform, drawn by Renderer (projection/view/model handled centrally).
    struct Transform
    {
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        glm::vec3 rotationDeg{0.0f, 0.0f, 0.0f}; // Euler degrees
        glm::vec3 scale{1.0f, 1.0f, 1.0f};

        glm::mat4 ToMatrix() const
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(rotationDeg.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotationDeg.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotationDeg.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, scale);
            return model;
        }
    };

    struct Entity
    {
        Transform transform{};
        const Mesh* mesh = nullptr;
        Shader* shader = nullptr;
        // Optional per-frame update hook to modify transform.
        std::function<void(Transform& transform, const Renderer& renderer)> update;
        // Bind extra uniforms/textures AFTER projection/view/model are set.
        std::function<void(Shader& shader, const Renderer& renderer)> bind;
    };

private:
    std::vector<Entity> m_Entities;
    Camera m_Camera;

public:
    Scene();
    ~Scene() = default;

    void Clear();
    void Reset();

    void AddEntity(const Entity& e) { m_Entities.push_back(e); }
    void ClearEntities() { m_Entities.clear(); }
    std::vector<Entity>& GetEntities() { return m_Entities; }
    const std::vector<Entity>& GetEntities() const { return m_Entities; }

    Camera& GetCamera() { return m_Camera; }
    const Camera& GetCamera() const { return m_Camera; }
};