#pragma once

#include "tests/Test.h"
#include <string>

namespace test {
    class TestClearColor : public Test
    {
    private:
        float m_ClearColor[4];
        bool m_CheckboxState = false;
        float m_Time = 0.f;
        float m_Speed = 5.f;
        bool m_PartyTime = false;
    public:
        TestClearColor(const std::string& name);
        ~TestClearColor();

        void OnAttach(Renderer& renderer) override;
        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer& renderer) override;
        void OnImGuiRender(Renderer& renderer) override;
        void OnDetach(Renderer& renderer) override;
        
        void ResetColor();
        
    };   
}
