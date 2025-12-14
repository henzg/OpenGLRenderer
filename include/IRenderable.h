#pragma once

#include "glm/glm.hpp"

class Renderer;

class IRenderable
{
public:
    virtual ~IRenderable() = default;
    virtual void Draw(const Renderer& renderer, const glm::mat4& view, const glm::mat4& projection) const = 0;
};