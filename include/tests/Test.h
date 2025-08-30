#pragma once

#include <string>

class Renderer;

namespace test {

class Test
{
private:
    const std::string m_Name;
public:
    Test(const std::string& name){}
    virtual ~Test() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender(Renderer& renderer) {}
};

class TestMenu
{
private:

public:

};

}
