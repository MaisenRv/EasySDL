#pragma once
#include "../../../../Math/types/Vec2.hpp"
#include "../../../utils/shadersUtils.hpp"
#include "../../../utils/pathList.hpp"
#include "../../../interface/IWindow.hpp"
#include "../shape.hpp"
#include "../../../utils/collitions.hpp"
#include "../../../interface/ICollitionObject.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL
{
    class Particle : public EasySDL::Shape, public EasySDL::ICollitionObject
    {
    private:
        // Particle info
        float _size;
        int _resolution;
        float _mass;
        float _angle = 0;


        void calculateVertex()
        {
            this->_vertexList.clear();
            // push center
            this->_vertexList.push_back(0);
            this->_vertexList.push_back(0);

            float angle = 0;
            float delta = (2.0f * float(M_PI)) / this->_resolution;
            for (size_t i = 0; i <= this->_resolution; i++)
            {
                angle += delta;
                float x = this->_size * std::cos(angle);
                float y = this->_size * std::sin(angle);
                this->_vertexList.push_back(x);
                this->_vertexList.push_back(y);
            }
            this->vertexCount = this->_vertexList.size() / 2;
        }

        void _onSetup() override {

            this->calculateVertex();
            this->_createVAOAndVBO();
            
            this->_vertexSrc = EasySDL::compileShader(GL_VERTEX_SHADER, EasySDL::BASIC_VERTEX_SHADER_PATH);
            this->_fragmentSrc = EasySDL::compileShader(GL_FRAGMENT_SHADER, EasySDL::BASIC_FRAGMENT_SHADER_PATH);
            this->program = glCreateProgram();
            glAttachShader(this->program, this->_vertexSrc);
            glAttachShader(this->program, this->_fragmentSrc);
            glLinkProgram(this->program);
        }

    public:
        Particle():_size(10),_resolution(20){
            this->_position = {0,0};
        };
        Particle(float x, float y, float size, int resolution) : _size(size), _resolution(resolution){
            this->_position = {x,y};
        };

        void draw(EasySDL::IWindow *w) override
        {
            if(this->isDeformable && this->geometryDirty){
                this->calculateVertex();
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
            glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertexCount);  
        }


        ~Particle()
        {
            glDeleteProgram(this->program);
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
            glDeleteBuffers(1,&(this->shapeVBO));
            glDeleteVertexArrays(1,&(this->shapeVAO));
        }

        bool IsColliding(EasySDL::Vec2 objectPosition) override{
            if(!this->isActivateCollitions)
                return false;

            if(this->_position.distance(objectPosition) < this->_size){
                this->isColliding = true;
            }else{
                this->isColliding = false;
            }
            return this->isColliding;
        }
        void updateBoxModel()override{}
        //-------------------- Getters and setters

        void setResolution(int resolution){
            this->_resolution = resolution;
            this->geometryDirty = true;
        }
    };
}
