#pragma once

#include <SDL2/SDL.h>

#include <BitMth/geometry/types/LineAttachmentTypes.hpp>
#include <BitMth/geometry/GeometryFactory.hpp>
#include <EasySDL/render/Renderer2D.hpp>
#include <EasySDL/render/types/PrimitiveTypes.hpp>
#include <EasySDL/objects/shape/Shape.hpp>

namespace EasySDL::objects{
    class Line : public Shape {
    private:
        BitMth::geometry::types::LineAttachmentTypes _lineAttachType = BitMth::geometry::types::LineAttachmentTypes::ATTACH_P0;

    public:
        void calculateVertices() override{
            if (_mesh.vertices.empty()){ 
                _mesh.vertices = BitMth::geometry::GeometryFactory<float>::makeLine(_lineAttachType);
                return;
            }
            BitMth::geometry::GeometryFactory<float>::fillLine(_mesh.vertices, _lineAttachType);
        }

        Line(const BitMth::linalg::Vec2<float>& p0, const BitMth::linalg::Vec2<float>& p1, GLfloat lineWidth) : Shape(p0) {
            _mesh.primitiveType = render::types::PrimitiveType::Lines;
            _transform.scale.x = p0.distance(p1);
            _transform.angle = p0.angleTo(p1);
            _material.lineWidth = lineWidth;
        }

        Line(const BitMth::linalg::Vec2<float>& p0, float angle, float length, GLfloat lineWidth) : Shape(p0){
            _mesh.primitiveType = render::types::PrimitiveType::Lines;
            this->_transform.scale.x = length;
            this->_transform.angle = angle;
            _material.lineWidth = lineWidth;
        }

        void render(render::Renderer2D& renderer,EasySDL::IWindow *w) override{ renderer.draw(w,*this); }

        // void shiftX(float delta)
        // {
        //     this->_position.x -= delta;
        // }
        //-------------------- Getters and setters
        
        [[nodiscard]] const BitMth::linalg::Vec2<float> getPosPoint0() const{
            if(_lineAttachType == BitMth::geometry::types::LineAttachmentTypes::ATTACH_P0) return getPosition();

            BitMth::linalg::Vec2<float> dir{ std::cos(_transform.angle), std::sin(_transform.angle) };
            switch(_lineAttachType){
                case BitMth::geometry::types::LineAttachmentTypes::ATTACH_P1:
                    return _transform.position + (dir * _transform.scale.x);

                case BitMth::geometry::types::LineAttachmentTypes::ATTACH_CENTER:
                    return this->_transform.position - dir * (this->_transform.scale.x * 0.5f);
            }
            return {};
        }

        [[nodiscard]] const BitMth::linalg::Vec2<float> getPosPoint1() const {
            if(_lineAttachType == BitMth::geometry::types::LineAttachmentTypes::ATTACH_P1) return getPosition();

            BitMth::linalg::Vec2<float> dir{ std::cos(_transform.angle), std::sin(_transform.angle) };

            switch(_lineAttachType){
                case BitMth::geometry::types::LineAttachmentTypes::ATTACH_P0:
                    return this->_transform.position + (dir * this->_transform.scale.x);
                case BitMth::geometry::types::LineAttachmentTypes::ATTACH_CENTER:
                    return this->_transform.position + dir * (this->_transform.scale.x * 0.5f);
            }
            return {};
        }

        void setLineAttachType(BitMth::geometry::types::LineAttachmentTypes attachType){
            if(attachType == _lineAttachType) return;
            
            BitMth::linalg::Vec2<float> p0 = getPosPoint0();
            BitMth::linalg::Vec2<float> p1 = getPosPoint1();

            _lineAttachType = attachType;
            // calculateVertices();

            // _transform.scale.x = p0.distance(p1);
            // _transform.angle   = p0.angleTo(p1);

            switch(this->_lineAttachType){
                case BitMth::geometry::types::LineAttachmentTypes::ATTACH_P0:     _transform.position = p0; break;
                case BitMth::geometry::types::LineAttachmentTypes::ATTACH_P1:     _transform.position = p1; break;
                case BitMth::geometry::types::LineAttachmentTypes::ATTACH_CENTER: _transform.position = p0.midpoint(p1); break;
            }
            _mesh.geometryDirty = true;
        }

        void setLineWidth(float lineWidth) { _material.lineWidth = lineWidth; }
        void setLength(float length){ _transform.scale.x = length; }

        [[nodiscard]] float getLength() const noexcept { return _transform.scale.x;}

    };

}