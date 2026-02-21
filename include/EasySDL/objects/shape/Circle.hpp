#pragma once

#include "../../interface/IWindow.hpp"
#include "../../render/geometry/Geometry2D.hpp"
#include "../../render/Renderer2D.hpp"
#include "shape.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL
{
    class Circle : public EasySDL::Shape
    {
    private:
        float _radius;
        int _resolution;

    public:
        void calculateVertices() override{
            Geometry2D<float>::buildCircle(this->_mesh, this->_radius, this->_resolution);
        }
    
        Circle(): Shape({0,0}),_radius(10),_resolution(20){};
        Circle(float x, float y, float radius, int resolution) 
            : Shape({x,y}),_radius(radius), _resolution(resolution){};

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
    };
}
