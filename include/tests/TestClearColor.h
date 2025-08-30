#pragma once

#include "tests/Test.h"
#include <string>

namespace test {
    class TestClearColor : public Test
    {
    private:
        float m_ClearColor[4];
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
