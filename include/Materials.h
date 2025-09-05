#pragma once

#include "glm/glm.hpp"
#include <string>

enum class MaterialName 
{
    NONE = 0, 
    EMERALD, JADE, OBSIDIAN, PEARL, RUBY, TURQUOISE, BRASS, BRONZE, CHROME, COPPER, GOLD, SILVER, 
    BLACK_PLASTIC, CYAN_PLASTIC, GREEN_PLASTIC, RED_PLASTIC, WHITE_PLASTIC, YELLOW_PLASTIC, 
    BLACK_RUBBER, CYAN_RUBBER, GREEN_RUBBER, RED_RUBBER, WHITE_RUBBER, YELLOW_RUBBER
};

struct MaterialElement
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    MaterialElement() : ambient(0.f), diffuse(0.f), specular(0.f), shininess(0.f) {}
    MaterialElement(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec, const float shin)
        : ambient(amb), diffuse(diff), specular(spec), shininess(shin) {}

    glm::vec3 getAmbient() {return ambient;}
    glm::vec3 getDiffuse() {return diffuse;}
    glm::vec3 getSpecular() {return specular;}
    float getShininess() {return shininess;}
};

class Material 
{
private:
    MaterialElement m_MaterialElement;

public:
    Material() : m_MaterialElement() {}
    
    Material(MaterialName materialName) 
    {
        setMaterial(materialName);
    }

    void setMaterial(MaterialName materialName)
    {
        switch(materialName)
        {
            case (MaterialName::EMERALD):
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.0215f, 0.1745f, 0.0215f),
                    glm::vec3(0.07568f, 0.61424f, 0.07568),
                    glm::vec3(0.633f, 0.727811f, 0.633f),
                    0.6f
                );
                break;
            case (MaterialName::JADE):
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.135f, 0.2225f, 0.1575f),
                    glm::vec3(0.54f, .89f, .63f),
                    glm::vec3(0.316228f, 0.316228f, 0.316228f),
                    0.1f
                );
                break;
            case (MaterialName::OBSIDIAN):
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.05375f, 0.05f, 0.06625f),
                    glm::vec3(0.18275f, .17f, .22525f),
                    glm::vec3(0.332741, 0.328634, 0.346435),
                    0.3
                );
                break;
            case (MaterialName::PEARL):
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.25f, 0.20725f, 0.20725f),
                    glm::vec3(1.0f, .829f, .829f),
                    glm::vec3(0.296648f, 0.296648f, 0.296648f),
                    0.088f
                );
                break;
            case (MaterialName::RUBY):
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.1745f, 0.01175f, 0.01175f),
                    glm::vec3(0.61424f, 0.04136f, 0.04136f),
                    glm::vec3(0.727811f, 0.626959f, 0.626959f),
                    0.6f
                );
                break;
            case (MaterialName::TURQUOISE):
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.1f, 0.18725f, 0.1745f),
                    glm::vec3(0.396f, 0.74151f, 0.69102f),
                    glm::vec3(0.297254f, 0.30829f, 0.306678f),
                    0.1f
                );
                break;
            case MaterialName::BRASS:
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.329412f, 0.223529f, 0.027451f),
                    glm::vec3(0.780392f, 0.568627f, 0.113725f),
                    glm::vec3(0.992157f, 0.941176f, 0.807843f),
                    0.21794872
                );
                break;
            case MaterialName::BRONZE:
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.2125f, 0.1275f, 0.054f),
                    glm::vec3(0.714f, 0.4284f, 0.18144f),
                    glm::vec3(0.393548f, 0.271906f, 0.166721f),
                    0.2
                );
                break;
            case MaterialName::CHROME:
                m_MaterialElement = MaterialElement(
                    glm::vec3(0.25f, 0.25f, 0.25f),
                    glm::vec3(0.4f, 0.4f, 0.4f),
                    glm::vec3(0.774597f, 0.774597f, 0.774597f),
                    0.6
                );
                break;
            case (MaterialName::NONE): default:
                m_MaterialElement = MaterialElement();
                break;
        }
    }

    const MaterialElement& getMaterialElement() const { return m_MaterialElement; }
    glm::vec3 getAmbient() {return m_MaterialElement.getAmbient();}
    glm::vec3 getDiffuse() {return m_MaterialElement.getDiffuse();}
    glm::vec3 getSpecular() {return m_MaterialElement.getSpecular();}
    float getShininess() {return m_MaterialElement.getShininess();}
};
