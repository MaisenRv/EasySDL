#pragma once

#include "../../interface/IWindow.hpp"
#include "../../render/geometry/Geometry2D.hpp"
#include "../../render/Renderer2D.hpp"
#include "shape.hpp"

#include <SDL2/SDL.h>

namespace EasySDL
{
    class Square : public EasySDL::Shape 
    {
    private:
        float _width;
        float _height;

    public:
        void calculateVertices() override{
            Geometry2D<float>::buildSquare(this->_mesh, this->_width, this->_height);
        }
        Square(float x, float y, float width, float height) : Shape({x,y}), _width(width), _height(height) {}

        void render(Renderer2D& renderer,EasySDL::IWindow *w) override{
            renderer.draw(w,*this);
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
