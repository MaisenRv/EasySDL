#pragma once
#include "./Line.hpp"
#include "../../types/Vec2.hpp"
#include <iostream>
#include <cstdio>
#include <cmath>

namespace EasySDL
{
    class ContraintLine : public EasySDL::Line
    {
    private:
        float _length;
        float _angle;
        void _calculateVertex(float x0, float y0)
        {

            float x1 = this->_vertexList[2];
            float y1 = this->_vertexList[3];
            this->_vertexList.clear();
            this->_vertexList.push_back(x0);
            this->_vertexList.push_back(y0);
            EasySDL::Vec2 p0{x0, y0};
            EasySDL::Vec2 p1{x1, y1};

            float x = p0.x + cos(this->_angle) * this->_length;
            float y = p0.y + sin(this->_angle) * this->_length;
            this->_vertexList.push_back(x);
            this->_vertexList.push_back(y);
        }

    public:
        ContraintLine(float x0, float y0, float x1, float y1, GLfloat lineWidth, float length) : Line(x0, y0, x1, y1, lineWidth), _length(length)
        {
            EasySDL::Vec2 p0{x0, y0};
            EasySDL::Vec2 p1{x1, y1};
            this->_angle = p0.angle(p1);
        }
        virtual void draw(EasySDL::Window *w)
        {
            this->_calculateVertex(this->_vertexList[0], this->_vertexList[1]);
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
        void update(float x0, float y0)
        {
            this->_calculateVertex(x0, y0);
        }

        void setAngle(float newAngle)
        {
            this->_angle = newAngle;
            this->_calculateVertex(this->_vertexList[0],this->_vertexList[1]);
        }
        float getAngle(){
            return this->_angle;
        }

        std::string getAngleStr(){
            char buf[32];
            std::snprintf(buf, sizeof(buf),"%.2f",this->_angle);
            std::string angleStr(buf);
            return angleStr;
        }
        std::string getAngleDegStr(){
            char buf[32];
            float degAngle = this->_angle *(180/M_PI);
            std::snprintf(buf, sizeof(buf),"%.1f",degAngle);
            std::string angleStr(buf);
            return angleStr;
        }
        float getLength(){
            return this->_length;
        }

        EasySDL::Vec2 getPosPoint2(){
            EasySDL::Vec2 result {this->_vertexList[2],this->_vertexList[3]};
            return result;
        }

    };
}