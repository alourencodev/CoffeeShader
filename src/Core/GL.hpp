#ifndef COFFEE_UTILS_GL_HPP
#define COFFEE_UTILS_GL_HPP

#include <glad/glad.h>

#include "Core/Log.hpp"

namespace coffee::utils
{

constexpr int32_t sizeofGLType(GLenum type)
{
    switch (type)
    {
        case GL_INT:
            return sizeof(GLint);
        case GL_INT_VEC2:
            return sizeof(GLint) * 2;
        case GL_INT_VEC3:
            return sizeof(GLint) * 3;
        case GL_INT_VEC4:
            return sizeof(GLint) * 4;
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        case GL_UNSIGNED_INT_VEC2:
            return sizeof(GLuint) * 2;
        case GL_UNSIGNED_INT_VEC3:
            return sizeof(GLuint) * 3;
        case GL_UNSIGNED_INT_VEC4:
            return sizeof(GLuint) * 4;
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_FLOAT_VEC2:
            return sizeof(GLfloat) * 2;
        case GL_FLOAT_VEC3:
            return sizeof(GLfloat) * 3;
        case GL_FLOAT_VEC4:
            return sizeof(GLfloat) * 4;
        default:
            logWarning("GL", "Trying to get the size of an unknown gl type.");
            return -1;
    }
}

}

#endif