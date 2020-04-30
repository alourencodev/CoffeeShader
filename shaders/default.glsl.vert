#version 410 core

in vec3 inPosition;

uniform mat4 uMVP;
uniform float uDummyInt;

out vec4 fColor;

void main()
{
    fColor = vec4(inPosition, 1.0 - uDummyInt);
    gl_Position = uMVP * vec4(inPosition, 1.0);
}