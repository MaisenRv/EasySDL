#pragma once
// #include "../../../Window.hpp"
#include "../../../utils/shadersUtils.hpp"
#include "../../../utils/pathList.hpp"
#include "../../../types/lineAttachmentTypes.hpp"
#include "../../../interface/IWindow.hpp"
#include "../shape.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL
{
    class Line : public EasySDL::Shape
    {
    protected:
        // Line info
        GLfloat _lineWidth;
        int _lineAttachType = EasySDL::ATTACH_P1;
        float _length = 0;
        float _coords[4] = {0,0,0,0};


        void _calculateVertex()
        {
            this->_vertexList.clear();
            Math::Vec2 p0{this->_coords[0], this->_coords[1]};
            Math::Vec2 p1{this->_coords[2], this->_coords[3]};
            this->_length = p0.distance(p1);

            if(this->_lineAttachType == EasySDL::ATTACH_P2){
                this->_vertexList.push_back(-this->_length);
                this->_vertexList.push_back(0);
                this->_vertexList.push_back(0);
                this->_vertexList.push_back(0);
                this->_angle = p1.angle(p0);
                this->_position = p1;
                return;
            }

            if(this->_lineAttachType == EasySDL::ATTACH_CENTER){
                float halfLength = this->_length / 2;
                this->_vertexList.push_back(-halfLength);
                this->_vertexList.push_back(0);
                this->_vertexList.push_back(halfLength);
                this->_vertexList.push_back(0);
                Math::Vec2 center = p0.betweenPoint(p1);
                this->_angle = center.angle(p1);
                this->_position = center;
                return;
            }

            this->_vertexList.push_back(0);
            this->_vertexList.push_back(0);
            this->_vertexList.push_back(this->_length);
            this->_vertexList.push_back(0);
            this->_angle = p0.angle(p1);
            this->_position = p0;
        }

        void _onSetup() override
        {
            
            this->_createVAOAndVBO();
            this->_vertexSrc = EasySDL::compileShader(GL_VERTEX_SHADER, EasySDL::BASIC_VERTEX_SHADER_PATH);
            this->_fragmentSrc = EasySDL::compileShader(GL_FRAGMENT_SHADER, EasySDL::BASIC_FRAGMENT_SHADER_PATH);
            this->program = glCreateProgram();
            glAttachShader(program, this->_vertexSrc);
            glAttachShader(program, this->_fragmentSrc);
            glLinkProgram(program);
        }

    public:
        Line(float x0, float y0, float x1, float y1, GLfloat lineWidth) : Shape({x0,y0}),_lineWidth(lineWidth)
        {
            this->vertexCount = 2;
            this->_coords[0] = x0;
            this->_coords[1] = y0;
            this->_coords[2] = x1;
            this->_coords[3] = y1;
            this->_calculateVertex();
            
        }

        void draw(EasySDL::IWindow *w) override
        {
            if(this->isDeformable && this->geometryDirty){
                this->_calculateVertex();
                this->_updateVertex();
                this->geometryDirty = false;
            }

            glUseProgram(this->program);
            GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
            GLint colorLoc = glGetUniformLocation(this->program, "u_Color"); 
            GLint posLoc = glGetUniformLocation(this->program,"u_Position");
            GLint angleLoc = glGetUniformLocation(this->program,"u_Rotation");
            GLint scaleLoc = glGetUniformLocation(this->program,"u_Scale");

            glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(colorLoc, _color[0], _color[1], _color[2], _color[3]);
            glUniform2f(posLoc,this->_position.x,this->_position.y);
            glUniform1f(angleLoc, this->_angle);
            glUniform2f(scaleLoc,this->_scale.x,this->_scale.y);

            glBindVertexArray(this->shapeVAO);
            glLineWidth(this->_lineWidth);
            // GL_LINES: dibuja segmentos independientes (dos vértices por línea).
            // GL_LINE_STRIP: dibuja una línea continua uniendo todos los vértices.
            // GL_LINE_LOOP: similar a LINE_STRIP, pero conectando el último vértice con el primero
            glDrawArrays(GL_LINES, 0, this->vertexCount);
           
        }

        ~Line()
        {
            glDeleteProgram(this->program);
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
            glDeleteBuffers(1,&(this->shapeVBO));
            glDeleteVertexArrays(1,&(this->shapeVAO));
        }

        void shiftX(float delta)
        {
            this->_position.x -= delta;
        }
        //-------------------- Getters and setters
        void setPositions(float x0, float y0, float x1, float y1){
            this->_coords[0] = x0;
            this->_coords[1] = y0;
            this->_coords[2] = x1;
            this->_coords[3] = y1;
            this->geometryDirty = true;
        }
        

        const std::vector<float>& getVertexList(){
            return this->_vertexList;
        }
        void setWidth(float width){
            this->_lineWidth = width;
        }

        float getLength(){
            return this->_length;
        }

        void setLength(float length){
            float c = std::cos(_angle);
            float s = std::sin(_angle);
            float cl = c * length;
            float sl = s * length;

            if(this->_lineAttachType == EasySDL::ATTACH_P1){
                float x = this->_coords[0] + cl;
                float y = this->_coords[1] + sl;
                this->_coords[2] = x;
                this->_coords[3] = y;
            }else if(this->_lineAttachType == EasySDL::ATTACH_P2){
                float x = this->_coords[2] + cl;
                float y = this->_coords[3] + sl;
                this->_coords[0] = x;
                this->_coords[1] = y;
            }else if(this->_lineAttachType == EasySDL::ATTACH_CENTER){
                float halfLength = length / 2;

                float x0 = this->_coords[0] + (c * halfLength);
                float y0 = this->_coords[1] + (s * halfLength);
                float x1 = this->_coords[2] + (c * halfLength);
                float y1 = this->_coords[3] + (s * halfLength);

                this->setPositions(x0,y0,x1,y1);
            }

            this->geometryDirty = true;
        }

        Math::Vec2 getPosPoint2(){
            float c = std::cos(_angle);
            float s = std::sin(_angle);

            if(this->_lineAttachType == EasySDL::ATTACH_P2){
                return {
                    _position.x,
                    _position.y
                };
            }else if(this->_lineAttachType == EasySDL::ATTACH_CENTER){
                float halfLength = this->_length / 2;
                return {
                    _position.x + c * halfLength,
                    _position.y + s * halfLength
                };
            }

            return {
                _position.x + c * _length,
                _position.y + s * _length
            };
        }

        void setLineAttachType(int attachType){
            this->_lineAttachType = attachType;
            this->geometryDirty = true;
        }

        void setPosPoint1( Math::Vec2 pos){
            this->_position = pos;
        }

    };

}