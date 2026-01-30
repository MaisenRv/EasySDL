#pragma once

#include "../../interface/IDrawable.hpp"
#include "../../interface/IInitializable.hpp"
#include "../../interface/IWindow.hpp"
#include "../../../Math/types/Vec2.hpp"
#include <vector>
#include <GL/glew.h>

namespace EasySDL{
    class Shape : public EasySDL::IDrawable, public EasySDL::IInitializable {
        protected:

            // properties
            float _color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
            Math::Vec2 _position;
            float _angle = 0;
            Math::Vec2 _scale = {1.0f,1.0f};

            //  Vertex info
            std::vector<float> _vertexList;
            bool isCreatedVertex = false;
            int vertexCount;
            GLuint shapeVBO;
            GLuint shapeVAO;


            // Shader info
            GLuint _vertexSrc = 0;
            GLuint _fragmentSrc = 0;

            // restrictions
            bool isMovable = false;
            bool isDeformable = false;
            bool isVertexUpdate = false;
            // flag
            bool geometryDirty = false;

            bool _restriction() override {
                return this->_vertexSrc && this->_fragmentSrc;
            }

            void _updateVertex(){
                glBindBuffer(GL_ARRAY_BUFFER,this->shapeVBO);

                glBufferData(
                    GL_ARRAY_BUFFER,
                    _vertexList.size() * sizeof(float),
                    _vertexList.data(),
                    this->isDeformable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
                );
            }


            void _createVAOAndVBO(){
                glGenVertexArrays(1,&(this->shapeVAO));
                glGenBuffers(1,&(this->shapeVBO));

                glBindVertexArray(this->shapeVAO);
                this->_updateVertex();

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                glBindVertexArray(0);
            }

        public:
            GLuint program;
            virtual ~Shape() = default;  

            void setColor(const float (&color)[4] ){
                for (size_t i = 0; i < 4; i++) this->_color[i] = color[i];
            }

            void setDeformable(bool deformable){
                this->isDeformable = deformable;
            }

            // POSITION
            Math::Vec2 getPosition(){
                return this->_position;
            }
            virtual void setPos(const Math::Vec2 newPos){
                this->_position = newPos;
            }

            // ANGLE
            void setAngle(float angle) { 
                this->_angle = angle; 
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

    };
}