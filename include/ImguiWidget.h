#pragma once

#include "imgui/imgui.h"
#include "glm/glm.hpp"

#include <string>

class ImguiWidget 
{
public:
    ImguiWidget(const std::string& label) : m_Label(label) {}
    ~ImguiWidget() = default;

    virtual void Draw() = 0;
    const std::string& GetLabel() const { return m_Label; }

    void SetEnabled(bool enabled) {m_isEnabled = enabled;}
    bool IsEnabled() const {return m_isEnabled;}
private:
    std::string m_Label;
    bool m_isEnabled = true;

};

class ImguiSliderFloat : public ImguiWidget
{
public:
    ImguiSliderFloat(const std::string& label, float* value, float min, float max)
        : ImguiWidget(label), m_Value(value), m_Min(min), m_Max(max) {}

    void Draw() override 
    {
        ImGui::SliderFloat(GetLabel().c_str(), m_Value, m_Min, m_Max);
    }

private:
    float* m_Value;
    float m_Min;
    float m_Max;
};


class ImguiColorEdit4 : public ImguiWidget
{
private:
    ImVec4* m_Color = nullptr;
    
public:
    ImguiColorEdit4(const std::string& label, ImVec4* color)
        : ImguiWidget(label), m_Color(color) {}
    void Draw() override
    {
        ImGui::ColorEdit4(GetLabel().c_str(), (float*)m_Color);    
    }
};

class ImguiColorPicker4 : public ImguiWidget
{
public:
    ImguiColorPicker4(const std::string& label, ImVec4* color, bool usePicker = false, bool withAlpha = true)
        : ImguiWidget(label), m_Color(color), m_UsePicker(usePicker), m_WithAlpha(withAlpha) {}
    void Draw() override
    {
        ImGui::ColorPicker4(GetLabel().c_str(), (float*)m_Color, m_UsePicker);
    }

private:
    ImVec4* m_Color = nullptr;
    bool m_UsePicker, m_WithAlpha;

};

class ImguiDragFloat3 : public ImguiWidget
{
public:
    ImguiDragFloat3(const std::string& label, glm::vec3* position, float change) 
        : ImguiWidget(label), m_Position(position), m_Change(change) {}

    void Draw() override
    {
        ImGui::DragFloat3(GetLabel().c_str(), (float*)m_Position, m_Change);
    }

private:
    glm::vec3* m_Position;
    float m_Change;

};
