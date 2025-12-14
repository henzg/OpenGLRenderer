#pragma once

#include "IRenderable.h"
#include "Camera.h"
#include <vector>
#include <memory>

class Scene
{
private:
    std::vector<std::unique_ptr<IRenderable>> m_Renderables;
    Camera m_Camera;

public:
    Scene();
    ~Scene() = default;

    void AddRenderable(std::unique_ptr<IRenderable> renderable);
    void RemoveRenderable(IRenderable* renderable);
    const std::vector<std::unique_ptr<IRenderable>>& GetRenderables() const { return m_Renderables; }

    Camera& GetCamera() { return m_Camera; }
    const Camera& GetCamera() const { return m_Camera; }
};