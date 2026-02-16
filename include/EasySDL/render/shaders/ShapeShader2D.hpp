#pragma once
#include "ShapeUniforms2D.hpp"
#include <GL/glew.h>


namespace EasySDL
{
    struct ShapeShader2D
    {
        GLint program = 0;
        ShapeUniforms2D uniforms;

        void init(){
            
            
        }

        void use(){
            glUseProgram(program);
        }

    };
    
}
