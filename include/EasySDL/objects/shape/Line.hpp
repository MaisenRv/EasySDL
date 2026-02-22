#pragma once

#include "../../types/LineAttachmentTypes.hpp"
#include "../../render/geometry/Geometry2D.hpp"
#include "../../interface/IWindow.hpp"
#include "../../render/Renderer2D.hpp"
#include "../../types/PrimitiveTypes.hpp"
#include "shape.hpp"

#include <SDL2/SDL.h>

namespace EasySDL
{
    class Line : public EasySDL::Shape
    {
    private:
        LineAttachmentTypes _lineAttachType = LineAttachmentTypes::ATTACH_P0;

        void _adjustments(Math::Vec2 p0, Math::Vec2 p1,float lineWidth){
            switch(this->_lineAttachType)
            {
                case LineAttachmentTypes::ATTACH_P0:
                    _transform.position = p0;
                    break;

                case LineAttachmentTypes::ATTACH_P1:
                    _transform.position = p1;
                    break;

                case LineAttachmentTypes::ATTACH_CENTER:
                    _transform.position = p0.betweenPoint(p1);
                    break;
            }
            this->_material.lineWidth = lineWidth;
        }
    public:
        void calculateVertices() override{
            Geometry2D<float>::buildLine(this->_mesh,this->_lineAttachType);
        }

        Line(Math::Vec2 p0, Math::Vec2 p1, GLfloat lineWidth) : Shape(p0)
        {
            this->_mesh.primitiveType = PrimitiveType::Lines;

            this->_transform.scale.x = p0.distance(p1);
            this->_transform.angle = p0.angle(p1);

            this->_adjustments(p0,p1,lineWidth);
        }
        Line(Math::Vec2 p0, float angle, float length,GLfloat lineWidth) : Shape(p0)
        {
            this->_mesh.primitiveType = PrimitiveType::Lines;

            this->_transform.scale.x = length;
            this->_transform.angle = angle;
            
            this->_adjustments(p0,this->getPosPoint1(),lineWidth);
        }

        void render(Renderer2D& renderer,EasySDL::IWindow *w) override{
            renderer.draw(w,*this);
        }

        // void shiftX(float delta)
        // {
        //     this->_position.x -= delta;
        // }
        //-------------------- Getters and setters
        
        Math::Vec2 getPosPoint0(){
            Math::Vec2 dir{
                std::cos(this->_transform.angle),
                std::sin(this->_transform.angle)
            };

            switch(this->_lineAttachType)
            {
                case LineAttachmentTypes::ATTACH_P0:
                    return this->_transform.position;

                case LineAttachmentTypes::ATTACH_P1:
                    return this->_transform.position + dir * this->_transform.scale.x;

                case LineAttachmentTypes::ATTACH_CENTER:
                    return this->_transform.position - dir * (this->_transform.scale.x * 0.5f);
            }
            return {};
        }

        Math::Vec2 getPosPoint1(){
            Math::Vec2 dir{
                std::cos(this->_transform.angle),
                std::sin(this->_transform.angle)
            };

            switch(this->_lineAttachType)
            {
                case LineAttachmentTypes::ATTACH_P0:
                    return this->_transform.position + dir * this->_transform.scale.x;

                case LineAttachmentTypes::ATTACH_P1:
                    return this->_transform.position;

                case LineAttachmentTypes::ATTACH_CENTER:
                    return this->_transform.position + dir * (this->_transform.scale.x * 0.5f);
            }
            return {};
        }

        void setLineAttachType(LineAttachmentTypes attachType){
            
            Math::Vec2 p0 = this->getPosPoint0();
            Math::Vec2 p1 = this->getPosPoint1();

            this->_lineAttachType = attachType;
            this->calculateVertices();

            this->_transform.scale.x = p0.distance(p1);
            this->_transform.angle   = p0.angle(p1);

            switch(this->_lineAttachType)
            {
                case LineAttachmentTypes::ATTACH_P0:     this->_transform.position = p0; break;
                case LineAttachmentTypes::ATTACH_P1:     this->_transform.position = p1; break;
                case LineAttachmentTypes::ATTACH_CENTER: this->_transform.position = p0.betweenPoint(p1); break;
            }
        }

        void setLineWidth(float width){
            this->_material.lineWidth = width;
        }

        float getLength(){
            return this->_transform.scale.x;
        }

        void setLength(float length){
            this->_transform.scale.x = length; 
        }
    };

}