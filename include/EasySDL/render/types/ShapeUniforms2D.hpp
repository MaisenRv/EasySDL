#pragma once

#include <GL/glew.h>

namespace EasySDL::render::types{
    struct ShapeUniforms2D{
        GLint windowSize = -1;
        GLint color = -1;
        GLint position = -1;
        GLint angle = -1;
        GLint scale = -1; 
        GLint offset = -1;
        GLint texture = -1;
    };
} 
