#pragma once

#include "imgui.h"
#include "string"

class DeveloperWindow {
public:
    DeveloperWindow(const std::string& title, ImVec2 initialPos, ImVec2 initialSize);
    ~DeveloperWindow() = default;
    
    void Draw();

private:
    std::string m_title;
    ImVec2 m_position, m_size;
};

