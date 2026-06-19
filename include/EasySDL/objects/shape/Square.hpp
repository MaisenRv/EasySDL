#pragma once

#include <EasySDL/interface/IWindow.hpp>
#include <EasySDL/render/Renderer2D.hpp>
#include <EasySDL/objects/shape/Shape.hpp>
#include <BitMth/geometry/GeometryFactory.hpp>

#include <SDL2/SDL.h>

namespace EasySDL::objects{
    class Square : public Shape {
    private:
        float _width;
        float _height;

    public:
        void calculateVertices() override{
            if (_mesh.vertices.empty()){    
                _mesh.vertices = BitMth::geometry::GeometryFactory<float>::makeSquare(_width,_height);
                return;
            }
            BitMth::geometry::GeometryFactory<float>::fillSquare(_mesh.vertices,_width,_height);
        }

        Square(float width, float height) : Shape({0,0}), _width(width), _height(height) {}
        Square(const BitMth::linalg::Vec2<float>& position, float width, float height) : Shape(position), _width(width), _height(height) {}

        void render(render::Renderer2D& renderer,EasySDL::IWindow *w) override{ renderer.draw(w,*this); }

        void setWidth(float width){
            this->_width = width;
            this->_mesh.geometryDirty = true;
        }
        void setHeight(float height){
            this->_height = height;
            this->_mesh.geometryDirty = true;
        }

        [[nodiscard]] float getWidth() const noexcept  { return _width; }
        [[nodiscard]] float getHeight() const noexcept { return _height; }
    };
}
