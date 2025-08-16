#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec4 ourPos;

uniform float xOffSet;

void main()
{
    ourPos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = ourPos;
    ourColor = aColor;
}
