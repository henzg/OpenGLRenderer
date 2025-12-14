#pragma once

#include <string>
#include "ResourceManager.h" // Required for ResourceManager& parameter
#include "Scene.h" // Required for Scene& parameter

class Renderer;

namespace test {

class Test
{
private:
    const std::string m_Name;
public:
    Test(const std::string& name, ResourceManager& resourceManager, Scene& scene)
        : m_Name(name) {}
    virtual ~Test() {}

    virtual void OnAttach(Renderer& renderer, ResourceManager& resourceManager, Scene& scene) {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender(Renderer& renderer) {}
    virtual void OnImGuiRender(Renderer& renderer) {}
    virtual void OnDetach(Renderer& renderer) {}

    const std::string GetName() { return m_Name; }
    void TestCleanup();
};
/*End of test namespace---------------------------------------------------------------------*/
}
