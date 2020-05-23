#ifndef COFFEE_DEFAULT_SHADERS_HPP
#define COFFEE_DEFAULT_SHADERS_HPP

namespace coffee::shader
{

const char k_defaultVertexSource[] = "                      \n\
#version 410 core                                           \n\
                                                            \n\
in vec3 inPosition;                                         \n\
                                                            \n\
uniform mat4 uMVP;                                          \n\
uniform vec3 uColor;                                        \n\
                                                            \n\
out vec4 fColor;                                            \n\
                                                            \n\
void main()                                                 \n\
{                                                           \n\
    fColor = vec4(uColor, 1.0);                             \n\
    gl_Position = uMVP * vec4(inPosition, 1.0);             \n\
}                                                           \n\
";


const char k_defaultFragmentSource[] = "                    \n\
#version 410 core                                           \n\
                                                            \n\
in vec4 fColor;                                             \n\
                                                            \n\
out vec4 outColor;                                          \n\
                                                            \n\
void main()                                                 \n\
{                                                           \n\
    outColor = fColor;                                      \n\
}                                                           \n\
";

}

#endif