#pragma once
#include "../../Window.hpp"
#include "../../utils/shadersUtils.hpp"
#include "../../utils/pathList.hpp"
#include "../../types/Vec2.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL
{
    class LineStrip
    {
    protected:
        // Line info
        GLfloat _lineWidth;
        float _color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

        //  Vertex info
        std::vector<float> _vertexList;

        // Shader info
        GLuint _vertexSrc;
        GLuint _fragmentSrc;


    public:
        GLuint program;
        int vertexCount;

        LineStrip(GLfloat lineWidth):_lineWidth(lineWidth) {}

        void draw(EasySDL::Window *w)
        {
            this->vertexCount = (int)(this->_vertexList.size() / 2);
            if (this->vertexCount == 0) return;
            
            glBindBuffer(GL_ARRAY_BUFFER, w->VBO);
            glBufferData(
                GL_ARRAY_BUFFER,
                this->_vertexList.size() * sizeof(float),
                this->_vertexList.data(),
                GL_DYNAMIC_DRAW);

            GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
            GLint colorLoc = glGetUniformLocation(this->program, "u_Color"); // Color
            glUseProgram(this->program);
            glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(colorLoc, this->_color[0], this->_color[1], this->_color[2], this->_color[3]);
            glBindVertexArray(w->VAO);
            glLineWidth(this->_lineWidth);
            glDrawArrays(GL_LINE_STRIP, 0, this->vertexCount);
        }
        void setup()
        {
            this->_vertexSrc = EasySDL::compileShader(GL_VERTEX_SHADER, EasySDL::BASIC_VERTEX_SHADER_PATH);
            this->_fragmentSrc = EasySDL::compileShader(GL_FRAGMENT_SHADER, EasySDL::BASIC_FRAGMENT_SHADER_PATH);
            this->program = glCreateProgram();
            glAttachShader(program, this->_vertexSrc);
            glAttachShader(program, this->_fragmentSrc);
            glLinkProgram(program);
        }

        void addPoint(Vec2 point){
            this->_vertexList.push_back(point.x);
            this->_vertexList.push_back(point.y);
        }

        ~LineStrip()
        {
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
        }

        //-------------------- Getters and setters
        void setColor(const float (&NewColor)[4])
        {
            for (size_t i = 0; i < 4; i++)
            {
                this->_color[i] = NewColor[i];
            }
        }
    };

}