#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 triPos;

void main()
{
    gl_Position = vec4(aPos.x + triPos.x, aPos.y + triPos.y, aPos.z, 1.0);
}
