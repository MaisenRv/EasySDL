#pragma once
#include "../../Window.hpp"
#include "../../types/Vec2.hpp"
#include "../../utils/shadersUtils.hpp"
#include "../../utils/pathList.hpp"
#include <SDL2/SDL.h>

namespace EasySDL
{
    class Square
    {
    private:
        int _width;
        int _height;
        EasySDL::Vec2 _position;
        float _color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

        //  Vertex info
        std::vector<float> _vertexList;

        // Shader info
        GLuint _vertexSrc;
        GLuint _fragmentSrc;
        void _calculateVertex()
        {
            this->_vertexList.clear();
            float hWidth = this->_width / 2;
            float hHeight = this->_height / 2;

            this->_vertexList.push_back(this->_position.x);
            this->_vertexList.push_back(this->_position.y);

            this->_vertexList.push_back(this->_position.x - hWidth);
            this->_vertexList.push_back(this->_position.y + hHeight);

            this->_vertexList.push_back(this->_position.x + hWidth);
            this->_vertexList.push_back(this->_position.y + hHeight);

            this->_vertexList.push_back(this->_position.x + hWidth);
            this->_vertexList.push_back(this->_position.y - hHeight);

            this->_vertexList.push_back(this->_position.x - hWidth);
            this->_vertexList.push_back(this->_position.y - hHeight);

            this->_vertexList.push_back(this->_position.x - hWidth);
            this->_vertexList.push_back(this->_position.y + hHeight);
        }

    public:
        GLuint program;
        int vertexCount = 6;

        Square(EasySDL::Vec2 pos, float width, float height) : _position(pos), _width(width), _height(height) {}

        void draw(EasySDL::Window *w)
        {
            this->_calculateVertex();
            glBindBuffer(GL_ARRAY_BUFFER, w->VBO);
            glBufferData(
                GL_ARRAY_BUFFER,
                this->_vertexList.size() * sizeof(float),
                this->_vertexList.data(),
                GL_DYNAMIC_DRAW);

            glUseProgram(this->program);
            GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
            GLint colorLoc = glGetUniformLocation(this->program, "u_Color");
            glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(colorLoc, this->_color[0], this->_color[1], this->_color[2], this->_color[3]);

            glBindVertexArray(w->VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertexCount);
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

        ~Square()
        {
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
        }
    };
}
