#version 410 core

in vec3 inPosition;

uniform mat4 uMVP;

out vec4 fColor;

void main()
{
    fColor = vec4(inPosition, 1.0);
    gl_Position = uMVP * vec4(inPosition, 1.0);
}