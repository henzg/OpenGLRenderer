#pragma once

#include <string>

class Renderer;

namespace test {

class Test
{
private:
    const std::string m_Name;
public:
    Test(const std::string& name){}
    virtual ~Test() {}

    virtual void OnAttach(Renderer& renderer) {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender(Renderer& renderer) {}
    virtual void OnImGuiRender(Renderer& renderer) {}
    virtual void OnDetach(Renderer& renderer) {}

    const std::string GetName() { return m_Name; }
    void TestCleanup();
};
/*End of test namespace---------------------------------------------------------------------*/
}
