#pragma once

#include "Test.h"
#include "imgui/imgui.h"


namespace test {

    class Test3DBasics : public Test 
    {
    private:
        float m_TextureMix = 0.0f;
        float m_Fov = 90.0f;
        ImVec4 m_WinColor = {.75f, 0.f, .30f, 1.f};

    public:
        Test3DBasics(const std::string& name);
        ~Test3DBasics();
        
        void OnAttach(Renderer& renderer) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& renderer) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;

    };
}
