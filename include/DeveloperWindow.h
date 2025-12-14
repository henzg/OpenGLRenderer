#pragma once

#include "ImguiWidget.h"
#include "tests/Test.h"
#include "Scene.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>


class DeveloperWindow {
public:
    DeveloperWindow(const std::string& title,ImVec2 initialPos, ImVec2 initialSize);
    ~DeveloperWindow() = default;
    
    void Draw(int mainWindowWidth, int mainWindowHeight, Renderer& renderer, float deltaTime, Scene& scene);

    /*--- Utilities for Widgets-------------------------------------------------------------*/
    template<typename T, typename... Args>
    void AddWidget(Args&&... args)
    {
        m_Widgets.push_back(std::make_unique<T>(std::forward<Args>(args)...));    
    }
    void RemoveWidget(const std::string& label);
    test::Test* GetCurrentTest() const;
    void ClearWidgets();

    void EnableWidget(const std::string& label);
    void DisableWidget(const std::string& label);
    void ToggleWidget(const std::string& label);
    bool IsWidgetEnabled(const std::string& label) const;
    /*--------------------------------------------------------------------------------------*/
    /*--- Utilities for Tests---------------------------------------------------------------*/
    template<typename T>
    void RegisterTest(const std::string& name, ResourceManager& resourceManager, Scene& scene)
    {
        m_Tests.push_back(std::make_pair(name, [&resourceManager, &scene, name]()
                                         {return std::make_unique<T>(name, resourceManager, scene);
                                         }));
    }
    test::Test* GetCurrentTest() { return m_CurrentTest.get(); }
    /*--------------------------------------------------------------------------------------*/


private:
    std::string m_Title;
    ImVec2 m_Position, m_Size;
    std::vector<std::unique_ptr<ImguiWidget>> m_Widgets;
    std::unique_ptr<test::Test> m_CurrentTest;
    std::vector<std::pair<std::string, std::function<std::unique_ptr<test::Test>()>>> m_Tests;

    ImguiWidget* FindWidget(const std::string& label);
    const ImguiWidget* FindWidget(const std::string& label) const;
};

