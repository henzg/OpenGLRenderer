#include "Scene.h"

Scene::Scene()
    : m_Camera() // Initialize camera with default values
{}

void Scene::Clear()
{
    m_Entities.clear();
}

void Scene::Reset()
{
    Clear();
    m_Camera = Camera(); // reset to default camera values
}