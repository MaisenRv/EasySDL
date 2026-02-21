#pragma once
#include "ShapeUniforms2D.hpp"
#include "./../../utils/pathList.hpp"
#include "./../../utils/shadersUtils.hpp"
#include "./../../interface/IWindow.hpp"
#include "./../core/Transform2D.hpp"
#include "./../core/Material2D.hpp"
#include <GL/glew.h>


namespace EasySDL
{
    struct ShapeShader2D
    {
        GLint program = 0;
        ShapeUniforms2D uniforms;

        void init(){
            if(program != 0) return;

            GLuint vertexShader = EasySDL::compileShader(GL_VERTEX_SHADER, EasySDL::BASIC_VERTEX_SHADER_PATH);
            GLuint fragmentShader = EasySDL::compileShader(GL_FRAGMENT_SHADER, EasySDL::BASIC_FRAGMENT_SHADER_PATH);
            program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            uniforms.windowSize = glGetUniformLocation(program, "u_WindowSize");
            uniforms.color      = glGetUniformLocation(program, "u_Color"); 
            uniforms.position   = glGetUniformLocation(program, "u_Position");
            uniforms.angle      = glGetUniformLocation(program, "u_Rotation");
            uniforms.scale      = glGetUniformLocation(program, "u_Scale");

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void use(){
            glUseProgram(program);
        }

        void updateUniforms(IWindow *w,const Transform2D &transform, const Material2D & material){
            glUniform2f(uniforms.windowSize, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(uniforms.color, material.color.r, material.color.g, material.color.b, material.color.a);
            glUniform2f(uniforms.position, transform.position.x, transform.position.y);
            glUniform1f(uniforms.angle, transform.angle);
            glUniform2f(uniforms.scale, transform.scale.x,transform.scale.y);
        }

        void del(){
            if(program == 0) return;
            glDeleteProgram(program);
            program = 0;
        }

    };
    
}
