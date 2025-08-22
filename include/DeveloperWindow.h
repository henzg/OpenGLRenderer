#pragma once

#include "imgui.h"
#include "string"
#include <memory>
#include <vector>

#include "ImguiWidget.h"

class DeveloperWindow {
public:
    DeveloperWindow(const std::string& title, ImVec2 initialPos, ImVec2 initialSize);
    ~DeveloperWindow() = default;
    
    // template allows us to have one push to Widgets vector no matter the widget
    template<typename T, typename... Args>
    void AddWidget(Args&&... args)
    {
        m_Widgets.push_back(std::make_unique<T>(std::forward<Args>(args)...));    
    }
    void Draw();

private:
    std::string m_Title;
    ImVec2 m_Position, m_Size;
    std::vector<std::unique_ptr<ImguiWidget>> m_Widgets;
};

