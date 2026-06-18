#pragma once

#include <EasySDL/interface/IWindow.hpp>
#include <EasySDL/render/Renderer2D.hpp>
#include <EasySDL/objects/shape/Shape.hpp>
#include <BitMth/geometry/GeometryFactory.hpp>

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace EasySDL::objects{
    class Circle : public Shape{
    private:
        float _radius;
        int _resolution;

    public:
        void calculateVertices() override{
            if (_mesh.vertices.empty()){    
                _mesh.vertices = BitMth::geometry::GeometryFactory<float>::makeCircle(_radius, _resolution);
                return;
            }
            BitMth::geometry::GeometryFactory<float>::fillCircle(_mesh.vertices,_radius,_resolution);
        }
    
        Circle(): Shape({0,0}),_radius(10),_resolution(20){};
        Circle(float x, float y, float radius, int resolution): Shape({x,y}),_radius(radius), _resolution(resolution){};

        void render(render::Renderer2D& renderer,EasySDL::IWindow *w) override{ renderer.draw(w,*this); }

        void setResolution(int resolution){
            _resolution = resolution;
            _mesh.geometryDirty = true;
        }
        void setRadius(int radius){
            _radius = radius;
            _mesh.geometryDirty = true;
        }

        [[nodiscard]] float getRadius()   const noexcept { return _radius; }
        [[nodiscard]] int getResolution() const noexcept { return _resolution; }
    };
}
