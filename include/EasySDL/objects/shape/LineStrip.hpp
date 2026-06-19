#pragma once

#include <EasySDL/interface/IWindow.hpp>
#include <EasySDL/render/Renderer2D.hpp>
#include <EasySDL/objects/shape/Shape.hpp>

#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <functional>

namespace EasySDL::objects{
 
    // struct LogicalPoint {
    //     double x;
    //     double y;
    // };
    
    class LineStrip : public Shape {   
    public:
        void calculateVertices() override{ _mesh.geometryDirty = true; }
        // std::vector<LogicalPoint> _points;

        LineStrip(GLfloat lineWidth) : Shape({0,0}){
            _material.lineWidth = lineWidth;
            _mesh.primitiveType = render::types::PrimitiveType::LineStrip;
        }

        void render(render::Renderer2D& renderer,EasySDL::IWindow *w) override{ renderer.draw(w,*this); }

        // void drawLineChart(EasySDL::IWindow *w,float domainMin, float domainMax,std::function<Math::Vec2(float,float)> map){
        //     if (_points.empty()) return;
            
        //     rebuildVertices(domainMin,domainMax,map);

        //     if (geometryDirty) {
        //         _updateVertex();
        //         geometryDirty = false;
        //     }

        //     glUseProgram(this->program);
        //     GLint loc = glGetUniformLocation(this->program, "u_WindowSize");
        //     GLint colorLoc = glGetUniformLocation(this->program, "u_Color"); // Color
        //     GLint posLoc = glGetUniformLocation(this->program,"u_Position");
        //     GLint angleLoc = glGetUniformLocation(this->program,"u_Rotation");
        //     GLint scaleLoc = glGetUniformLocation(this->program,"u_Scale");

        //     glUniform2f(loc, (float)w->getWidth(), (float)w->getHeight());
        //     glUniform4f(colorLoc, this->_color[0], this->_color[1], this->_color[2], this->_color[3]);
        //     glUniform2f(posLoc,this->_position.x,this->_position.y);
        //     glUniform1f(angleLoc, this->_angle);
        //     glUniform2f(scaleLoc,this->_scale.x,this->_scale.y);

        //     glBindVertexArray(this->shapeVAO);
        //     glLineWidth(this->_lineWidth);
        //     glDrawArrays(GL_LINE_STRIP, 0, this->vertexCount);

        // }

        // void rebuildVertices(float domainMin, float domainMax,std::function<Math::Vec2(float,float)> map)
        // {
        //     _vertexList.clear();
            
        //     for (auto& p : _points)
        //     {
        //         if (p.x < domainMin || p.x > domainMax)
        //             continue;

        //         Math::Vec2 pV(map(p.x,p.y));
        //         _vertexList.push_back(pV.x);
        //         _vertexList.push_back(pV.y);
        //     }
        //     this->vertexCount = (int)(this->_vertexList.size() / 2);
        //     geometryDirty = true;
        // }


        void addPoint(const BitMth::linalg::Vec2<float>& point){
            _mesh.vertices.push_back(point);
        }

        // void addPointLineChart(Math::Vec2 point){
        //     this->_points.push_back({point.x, point.y});
        // }

        // void removeFirstPoint(){
        //     this->_mesh.removeFirstPoint();
        // }

        // void shiftX(float delta,EasySDL::IWindow *w){
        //     this->_position.x -= delta;
        // }

        // void updateAllPoint(std::function<Math::Vec2(float x,float y)> updateFunction){
        //     std::vector<float> copyPoints(this->_vertexList);
        //     this->_vertexList.clear();
        //     for (size_t i = 0; i < copyPoints.size(); i += 2)
        //     {
        //         Math::Vec2 newPoints = updateFunction(copyPoints[i], copyPoints[i+1]);
        //         this->_vertexList.push_back(newPoints.x);
        //         this->_vertexList.push_back(newPoints.y);
        //     }
        // }

        void clearVertexList(){ _mesh.clear(); }

        [[nodiscard]] int getVertexSize() const noexcept { return _mesh.vertexCount(); }

        // std::vector<float> &getVertexList(){
        //     return this->_vertexList;
        // }
    };

}