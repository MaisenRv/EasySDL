#pragma once
#include "../../../Window.hpp"
#include "../../../../Math/types/Vec2.hpp"
#include "../../../utils/shadersUtils.hpp"
#include "../../../utils/pathList.hpp"
#include "../../../../Math/transformation/rotation2D.hpp"
#include "../shape.hpp"
#include <SDL2/SDL.h>

namespace EasySDL
{
    class Square : public EasySDL::Shape 
    {
    private:
        int _width;
        int _height;
        EasySDL::Vec2 _position;
        float _scale = 1;

        //  Vertex info
        float _angle = 0;

        // boundaries
        Vec2 _topLeft;
        Vec2 _topRight;
        Vec2 _bottomRight;
        Vec2 _bottomLeft;

        void _calculateVertex()
        {
            this->_vertexList.clear();

            std::vector<float> vertexCopy;
            vertexCopy.push_back(this->_position.x);
            vertexCopy.push_back(this->_position.y);

            vertexCopy.push_back(this->_topLeft.x);
            vertexCopy.push_back(this->_topLeft.y);

            vertexCopy.push_back(this->_topRight.x);
            vertexCopy.push_back(this->_topRight.y);

            vertexCopy.push_back(this->_bottomRight.x);
            vertexCopy.push_back(this->_bottomRight.y);

            vertexCopy.push_back(this->_bottomLeft.x);
            vertexCopy.push_back(this->_bottomLeft.y);

            vertexCopy.push_back(this->_topLeft.x);
            vertexCopy.push_back(this->_topLeft.y);

            for(size_t i = 0; i < vertexCopy.size();  i += 2){
                EasySDL::Vec2 result = EasySDL::rotate2D(
                    {vertexCopy[i],vertexCopy[i+1]},
                    this->_angle,
                    this->_position
                );
                this->_vertexList.push_back(result.x);
                this->_vertexList.push_back(result.y);
            }
        }

        void _updateBoundaries(){
            float hWidth  = this->_width / 2;
            float hHeight = this->_height / 2;

            float xLeft   = this->_position.x - hWidth  * this->_scale;
            float xRight  = this->_position.x + hWidth  * this->_scale;
            float yTop    = this->_position.y + hHeight * this->_scale;
            float ybottom = this->_position.y - hHeight * this->_scale;

            this->_topLeft     = {xLeft  ,yTop};
            this->_topRight    = {xRight ,yTop};
            this->_bottomRight = {xRight ,ybottom};
            this->_bottomLeft  = {xLeft  ,ybottom};
            this->_calculateVertex();
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
        Square(EasySDL::Vec2 pos, float width, float height) : _position(pos), _width(width), _height(height) {
            this->vertexCount = 6;
            this->_updateBoundaries();
        }

        void draw(EasySDL::Window *w) override
        {
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


        ~Square()
        {
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
        }
	// --------- GETTERS SETTERS


    void setPos(const EasySDL::Vec2 & newPos){
        this->_position = newPos;
        this->_updateBoundaries();
    }

    void setAngle(const float angle){
        this->_angle = angle;
        this->_calculateVertex();
    }

    void setScale(float scale){
        this->_scale = scale;
        this->_updateBoundaries();
    }

    };
}
