#include "Scene.h"
#include <algorithm>

Scene::Scene()
    : m_Camera() // Initialize camera with default values
{}

void Scene::AddRenderable(std::unique_ptr<IRenderable> renderable)
{
    m_Renderables.push_back(std::move(renderable));
}

void Scene::RemoveRenderable(IRenderable* renderable)
{
    // Find the unique_ptr owning the raw pointer and erase it
    m_Renderables.erase(
        std::remove_if(m_Renderables.begin(), m_Renderables.end(),
            [renderable](const std::unique_ptr<IRenderable>& p) {
                return p.get() == renderable;
            }),
        m_Renderables.end());
}