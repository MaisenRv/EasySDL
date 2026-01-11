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
    class RoundedRectagle : public EasySDL::Shape
    {
        private:
            float _width;
            float _height;
            float _radius;
            int _resolution;

            void _calculateCorner(float delta, int cornerNumberVertex,int quadrant){
                if(quadrant < 0 || quadrant > 4){
                    std::cerr << "NO existe el cuadrate: " << quadrant << std::endl;
                    return;
                }
                
                EasySDL::Vec2 quadrantV = {0,0};

                float angle = 0;
                float end = float(M_PI_2);

                if(quadrant == 1) quadrantV = {1,-1};
                else if (quadrant == 2) {
                    quadrantV = {-1,-1};
                    angle = float(M_PI_2);
                    end = -float(M_PI);
                }
                else if (quadrant == 3) {
                    quadrantV = {-1,1};
                    angle = -float(M_PI);
                    end = -float(M_PI_2);
                }
                else{
                    quadrantV = {1,1};
                    angle = -float(M_PI_2);   
                    end = 0;
                }

                float x_ = (this->_width/2) * quadrantV.x;
                float y_ = (this->_height/2) * quadrantV.y;

                for (size_t i = 0; i <= cornerNumberVertex; i++)
                {
                    this->_vertexList.push_back(x_ + (this->_radius * std::cos(angle)));
                    this->_vertexList.push_back(y_ - (this->_radius * std::sin(angle))); 
                    angle += delta;
                }
                this->_vertexList.push_back(x_ + (this->_radius * std::cos(end)));
                this->_vertexList.push_back(y_ - (this->_radius * std::sin(end)));
                
                if(quadrant == 4){
                    this->_vertexList.push_back(x_ + (this->_radius * std::cos(end)));
                    this->_vertexList.push_back(-y_ - (this->_radius * std::sin(end)));
                }
            }

            void _calculateVertex(){
                this->_vertexList.clear();
                // push center
                this->_vertexList.push_back(0);
                this->_vertexList.push_back(0);

                if(this->_resolution % 4 != 0){
                    this->_resolution += 4 - (this->_resolution % 4);
                }

                int cornerNumberVertex = (int)(this->_resolution / 4) + 1;
                float cornerDelta = float(M_PI_2) / cornerNumberVertex;

                this->_calculateCorner(cornerDelta,cornerNumberVertex,1);
                this->_calculateCorner(cornerDelta,cornerNumberVertex,2);
                this->_calculateCorner(cornerDelta,cornerNumberVertex,3);
                this->_calculateCorner(cornerDelta,cornerNumberVertex,4);

                this->vertexCount = this->_vertexList.size() / 2;

            }
            void _onSetup() override {
                this->_calculateVertex();
                this->_createVAOAndVBO();
                
                this->_vertexSrc = EasySDL::compileShader(GL_VERTEX_SHADER, EasySDL::BASIC_VERTEX_SHADER_PATH);
                this->_fragmentSrc = EasySDL::compileShader(GL_FRAGMENT_SHADER, EasySDL::BASIC_FRAGMENT_SHADER_PATH);
                this->program = glCreateProgram();
                glAttachShader(this->program, this->_vertexSrc);
                glAttachShader(this->program, this->_fragmentSrc);
                glLinkProgram(this->program);
            }

        public:
            RoundedRectagle(EasySDL::Vec2 position,float width,float height, float radius, int resolution) 
            : _width(width),_height(height),_radius(radius),_resolution(resolution)
            {
                this->_position = position;
            }
            void draw(EasySDL::IWindow *w) override{
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

                glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
                glUniform4f(colorLoc, _color[0], _color[1], _color[2], _color[3]);
                glUniform2f(posLoc,this->_position.x,this->_position.y);
                glUniform1f(angleLoc, this->_angle);

                glBindVertexArray(this->shapeVAO);
                glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertexCount); 

            }
            ~RoundedRectagle(){
                glDeleteProgram(this->program);
                glDeleteShader(this->_vertexSrc);
                glDeleteShader(this->_fragmentSrc);
                glDeleteBuffers(1,&(this->shapeVBO));
                glDeleteVertexArrays(1,&(this->shapeVAO));
            }

    };

}