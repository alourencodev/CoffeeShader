#version 410 core

in vec3 inPosition;
in vec3 inNormal;

uniform mat4 uMVP;

out vec3 fPos;
out vec3 fNormal;

void main()
{
    fNormal = inNormal;
    fPos = inPosition;
    gl_Position = uMVP * vec4(inPosition, 1.0);
}