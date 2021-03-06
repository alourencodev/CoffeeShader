#version 410 core

in vec3 inPosition;

uniform mat4 uMVP;
uniform float uGreen;
uniform int uInt;

out vec4 fColor;

void main()
{
    fColor = vec4(0.0, uGreen + uInt, 0.0, 1.0);
    gl_Position = uMVP * vec4(inPosition, 1.0);
}