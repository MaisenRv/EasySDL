#pragma once
#include "../../../utils/shadersUtils.hpp"
#include "../../../utils/pathList.hpp"
#include "../../../../Math/types/Vec2.hpp"
#include "../../../interface/IWindow.hpp"
#include "../shape.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <functional>

namespace EasySDL
{
 
    struct LogicalPoint {
        double x;
        double y;
    };
    class LineStrip : public EasySDL::Shape
    {
    protected:
        // Line info
        GLfloat _lineWidth;

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
        std::vector<LogicalPoint> _points;
        LineStrip(GLfloat lineWidth) : Shape({0,0}),_lineWidth(lineWidth) {}

        void draw(EasySDL::IWindow *w) override
        {
            this->vertexCount = (int)(this->_vertexList.size() / 2);
            if (this->vertexCount == 0) return;

            if(this->isDeformable && this->geometryDirty){
                this->_updateVertex();
                this->geometryDirty = false;
            }

            glUseProgram(this->program);
            GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
            GLint colorLoc = glGetUniformLocation(this->program, "u_Color"); // Color
            GLint posLoc = glGetUniformLocation(this->program,"u_Position");
            GLint angleLoc = glGetUniformLocation(this->program,"u_Rotation");
            GLint scaleLoc = glGetUniformLocation(this->program,"u_Scale");

            glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(colorLoc, this->_color[0], this->_color[1], this->_color[2], this->_color[3]);
            glUniform2f(posLoc,this->_position.x,this->_position.y);
            glUniform1f(angleLoc, this->_angle);
            glUniform2f(scaleLoc,this->_scale.x,this->_scale.y);

            glBindVertexArray(this->shapeVAO);
            glLineWidth(this->_lineWidth);
            glDrawArrays(GL_LINE_STRIP, 0, this->vertexCount);
        }
        void drawLineChart(EasySDL::IWindow *w,float domainMin, float domainMax,std::function<Math::Vec2(float,float)> map){
            if (_points.empty()) return;
            
            rebuildVertices(domainMin,domainMax,map);

            if (geometryDirty) {
                _updateVertex();
                geometryDirty = false;
            }

            glUseProgram(this->program);
            GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
            GLint colorLoc = glGetUniformLocation(this->program, "u_Color"); // Color
            GLint posLoc = glGetUniformLocation(this->program,"u_Position");
            GLint angleLoc = glGetUniformLocation(this->program,"u_Rotation");
            GLint scaleLoc = glGetUniformLocation(this->program,"u_Scale");

            glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
            glUniform4f(colorLoc, this->_color[0], this->_color[1], this->_color[2], this->_color[3]);
            glUniform2f(posLoc,this->_position.x,this->_position.y);
            glUniform1f(angleLoc, this->_angle);
            glUniform2f(scaleLoc,this->_scale.x,this->_scale.y);

            glBindVertexArray(this->shapeVAO);
            glLineWidth(this->_lineWidth);
            glDrawArrays(GL_LINE_STRIP, 0, this->vertexCount);

        }

        void rebuildVertices(float domainMin, float domainMax,std::function<Math::Vec2(float,float)> map)
        {
            _vertexList.clear();
            
            for (auto& p : _points)
            {
                if (p.x < domainMin || p.x > domainMax)
                    continue;

                Math::Vec2 pV(map(p.x,p.y));
                _vertexList.push_back(pV.x);
                _vertexList.push_back(pV.y);
            }
            this->vertexCount = (int)(this->_vertexList.size() / 2);
            geometryDirty = true;
        }


        void addPoint(Math::Vec2 point)
        {
            this->_vertexList.push_back(point.x);
            this->_vertexList.push_back(point.y);
            this->geometryDirty = true;
        }

        void addPointLineChart(Math::Vec2 point){
            this->_points.push_back({point.x, point.y});
        }

        ~LineStrip()
        {
            glDeleteProgram(this->program);
            glDeleteShader(this->_vertexSrc);
            glDeleteShader(this->_fragmentSrc);
            glDeleteBuffers(1,&(this->shapeVBO));
            glDeleteVertexArrays(1,&(this->shapeVAO));
        }

        void removeFirstPoint()
        {
            if (!this->_vertexList.empty())
            {
                this->_vertexList.erase(this->_vertexList.begin());
                this->_vertexList.erase(this->_vertexList.begin());
            }
        }

        void shiftX(float delta,EasySDL::IWindow *w){
            this->_position.x -= delta;
        }

        void updateAllPoint(std::function<Math::Vec2(float x,float y)> updateFunction){
            std::vector<float> copyPoints(this->_vertexList);
            this->_vertexList.clear();
            for (size_t i = 0; i < copyPoints.size(); i += 2)
            {
                Math::Vec2 newPoints = updateFunction(copyPoints[i], copyPoints[i+1]);
                this->_vertexList.push_back(newPoints.x);
                this->_vertexList.push_back(newPoints.y);
            }
        }

        void clearVertexList(){
            this->_vertexList.clear();
        }

        //-------------------- Getters and setters

        int getVertexSize()
        {
            return this->_vertexList.size() / 2;
        }

        std::vector<float> &getVertexList()
        {
            return this->_vertexList;
        }
    };

}