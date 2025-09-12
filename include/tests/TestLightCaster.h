#pragma once

#include "tests/Test.h"
#include "Mesh.h"

class Renderer;
class VertexArray;
class VertexBuffer;


namespace test {
    class TestLightCaster : public Test {
    private:
        const std::string m_CubeVAOName = "cubeCaster";
        const std::string m_LightVAOName = "lightCaster";

        Renderer& m_Renderer;
        VertexBuffer* m_VertexBuffer = nullptr;
        VertexArray* m_ObjectVAO = nullptr;
        VertexArray* m_LightVAO = nullptr;
        std::unique_ptr<Mesh> MainCube = Mesh::CreateCube(CubeFeature::All);
    public:
        TestLightCaster(const std::string& name, Renderer& renderer);
        ~TestLightCaster() = default;

        void OnAttach();
        void OnUpdate();
        void OnRender();
        void OnImGuiRenderer();
        void OnDetach();

    };


}
