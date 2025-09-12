#include "tests/TestLightCaster.h"

#include "Renderer.h"

namespace test {
    TestLightCaster::TestLightCaster(const std::string& name, Renderer& renderer) : Test(name), m_Renderer(renderer) {}

   void TestLightCaster::OnAttach() {
        
    }
    void TestLightCaster::OnUpdate() {}
    void TestLightCaster::OnRender() {
        //m_Renderer.AddMesh("CasterCube", std::move(MainCube));
    }
    void TestLightCaster::OnImGuiRenderer() {}
    void TestLightCaster::OnDetach() {}
}
