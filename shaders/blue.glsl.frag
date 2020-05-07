#version 410 core

in vec4 fColor;

uniform float uFragBlue;

out vec4 outColor;

void main()
{
    outColor = vec4(fColor.xy, uFragBlue, 1.0);
}