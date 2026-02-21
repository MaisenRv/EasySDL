#pragma once

#include "../../render/geometry/Geometry2D.hpp"
#include "../../interface/IWindow.hpp"
#include "../../render/Renderer2D.hpp"
#include "shape.hpp"

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
  
        public:
            void calculateVertices() override{
                Geometry2D<float>::buildRoundedRectangle(
                    this->_mesh,
                    this->_width,
                    this->_height,
                    this->_radius,
                    this->_resolution
                );
            }

            RoundedRectagle(float x, float y,float width,float height, float radius, int resolution) 
                : Shape({x,y}),_width(width),_height(height),_radius(radius),_resolution(resolution){}

            void render(Renderer2D& renderer,EasySDL::IWindow *w) override{
                renderer.draw(w,*this);
            }
            
            
            void setResolution(int resolution){
                this->_resolution = resolution;
                this->_mesh.geometryDirty = true;
            }
            void setRadius(int radius){
                this->_radius = radius;
                this->_mesh.geometryDirty = true;
            }
            void setWidth(float width){
                this->_width = width;
                this->_mesh.geometryDirty = true;
            }
            void setHeight(float height){
                this->_height = height;
                this->_mesh.geometryDirty = true;
            }
    };

}