#pragma once
#include "../../Window.hpp"
#include "../../utils/shadersUtils.hpp"
#include "../../utils/pathList.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL
{
    class Line
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

        void _calculateVertex(float x0, float y0, float x1, float y1)
        {
            this->_vertexList.clear();
            this->_vertexList.push_back(x0);
            this->_vertexList.push_back(y0);
            this->_vertexList.push_back(x1);
            this->_vertexList.push_back(y1);
        }

    public:
        GLuint program;
        const int vertexCount = 2;

        Line(float x0, float y0, float x1, float y1, GLfloat lineWidth) : _lineWidth(lineWidth)
        {
            this->_calculateVertex(x0,y0,x1,y1);
        }

        virtual void draw(EasySDL::Window *w)
        {
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
            glDrawArrays(GL_LINES, 0, this->vertexCount);

            // GL_LINES: dibuja segmentos independientes (dos vértices por línea).
            // GL_LINE_STRIP: dibuja una línea continua uniendo todos los vértices.
            // GL_LINE_LOOP: similar a LINE_STRIP, pero conectando el último vértice con el primero
        }
        void update(float x0, float y0, float x1, float y1){
            this->_calculateVertex(x0,y0,x1,y1);
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

        ~Line()
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
        void setPositions(float x0, float y0, float x1, float y1){
            this->_calculateVertex(x0,y0,x1,y1);
        }
    };

}