#version 410 core

in vec3 inPosition;

uniform mat4 mvp;

out vec4 fColor;

void main()
{
    fColor = vec4(0.0, 1.0, 0.0, 1.0);
    gl_Position = mvp * vec4(inPosition, 1.0);
}