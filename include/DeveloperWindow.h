#pragma once

#include "ImguiWidget.h"
#include "tests/Test.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>


class DeveloperWindow {
public:
    DeveloperWindow(const std::string& title,ImVec2 initialPos, ImVec2 initialSize);
    ~DeveloperWindow() = default;
    
    void Draw(int mainWindowWidth, int mainWindowHeight);

    /*--- Utilities for Widgets-------------------------------------------------------------*/
    template<typename T, typename... Args>
    void AddWidget(Args&&... args)
    {
        m_Widgets.push_back(std::make_unique<T>(std::forward<Args>(args)...));    
    }
    void ClearWidgets();
    /*--------------------------------------------------------------------------------------*/
    /*--- Utilities for Tests---------------------------------------------------------------*/
    template<typename T>
    void RegisterTest(const std::string& name)
    {
        m_Tests.push_back(std::make_pair(name, [name](){ return std::make_unique<T>(name); }));
    }
    test::Test* GetCurrentTest() { return m_CurrentTest.get(); }
    /*--------------------------------------------------------------------------------------*/


private:
    std::string m_Title;
    ImVec2 m_Position, m_Size;
    std::vector<std::unique_ptr<ImguiWidget>> m_Widgets;
    std::unique_ptr<test::Test> m_CurrentTest;
    std::vector<std::pair<std::string, std::function<std::unique_ptr<test::Test>()>>> m_Tests;
};

