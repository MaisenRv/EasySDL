#pragma once
#include "../../../../Math/types/Vec2.hpp"
#include "../../../utils/shadersUtils.hpp"
#include "../../../utils/pathList.hpp"
#include "../../../Window.hpp"
#include "../shape.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL
{
    class Particle : public EasySDL::Shape
    {
    private:
        // Particle info
        float _size;
        int _resolution;
        EasySDL::Vec2 _position;
        float _mass;


        void calculateVertex()
        {
            this->_vertexList.clear();
            // push center
            this->_vertexList.push_back(this->_position.x);
            this->_vertexList.push_back(this->_position.y);

            float angle = 0;
            float delta = (2.0f * float(M_PI)) / this->_resolution;
            for (size_t i = 0; i <= this->_resolution; i++)
            {
                angle += delta;
                float x = this->_position.x + this->_size * std::cos(angle);
                float y = this->_position.y + this->_size * std::sin(angle);
                this->_vertexList.push_back(x);
                this->_vertexList.push_back(y);
            }
        }

        void _onSetup() override {
            this->_vertexSrc = EasySDL::compileShader(GL_VERTEX_SHADER, EasySDL::BASIC_VERTEX_SHADER_PATH);
            this->_fragmentSrc = EasySDL::compileShader(GL_FRAGMENT_SHADER, EasySDL::BASIC_FRAGMENT_SHADER_PATH);
            this->program = glCreateProgram();
            glAttachShader(program, this->_vertexSrc);
            glAttachShader(program, this->_fragmentSrc);
            glLinkProgram(program);
        }

    public:
        Particle(): _position{0, 0}, _size(5),_resolution(20){};
        Particle(float x, float y, float size, int resolution) : _position{x, y}, _size(size), _resolution(resolution){};

        void draw(EasySDL::Window *w) override
        {
            this->calculateVertex();
            this->vertexCount = this->_vertexList.size() / 2;
            // 1) Subir datos al VBO:
            glBindBuffer(GL_ARRAY_BUFFER, w->VBO);
            glBufferData(
                GL_ARRAY_BUFFER,
                this->_vertexList.size() * sizeof(float),
                this->_vertexList.data(),
                GL_DYNAMIC_DRAW);

            // 2) Activar shader y pasar la uniform:
            GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
            GLint colorLoc = glGetUniformLocation(this->program, "u_Color"); // Color
            glUseProgram(this->program);
            glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(colorLoc, this->_color[0], this->_color[1], this->_color[2], this->_color[3]);

            // 3) Dibujar con el VAO ya configurado:
            glBindVertexArray(w->VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertexCount);
        }



        void update()
        {
            this->_position.x += 1;
        }

        ~Particle()
        {
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
        }

        //-------------------- Getters and setters

        EasySDL::Vec2 getPos(){
            return this->_position;
        }
        void setPos(const EasySDL::Vec2 newPos){
            this->_position = newPos;
        }

    };
}
