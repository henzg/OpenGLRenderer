#pragma once

#include "imgui.h"
#include "string"

class DeveloperWindow {
public:
    DeveloperWindow(const std::string& title, ImVec2 initialPos, ImVec2 initialSize);
    ~DeveloperWindow() = default;
    void BindFloat(const char* label, float* value, float min, float max);
    
    void Draw();

private:
    std::string m_title;
    ImVec2 m_position, m_size;
    const char* m_floatLabel = nullptr;
    float* m_floatPtr = nullptr;
    float m_floatMin = 0.0f;
    float m_floatMax = 1.0f;
};

