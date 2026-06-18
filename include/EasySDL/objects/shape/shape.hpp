#pragma once

#include <GL/glew.h>

#include <EasySDL/interface/IDrawable.hpp>
#include <EasySDL/interface/IInitializable.hpp>
#include <EasySDL/render/core/Transform2D.hpp>
#include <EasySDL/render/core/Material2D.hpp>
#include <EasySDL/render/geometry/Mesh2D.hpp>
#include <EasySDL/render/opengl/GLMesh2D.hpp>

namespace EasySDL::objects{
    class Shape : public EasySDL::IDrawable, public EasySDL::IInitializable {
        protected:
            render::Transform2D<float> _transform;
            render::Material2D<float> _material;
            render::Mesh2D<float> _mesh;
            render::gl::GLMesh2D<float> _glMesh;

            void _onSetup() override{
                this->calculateVertices();
                _glMesh.create();
                this->updateVertex(); 
            }

        public:

            virtual ~Shape() = default;
            explicit Shape(const BitMth::linalg::Vec2<float>& position):_transform(position){}

            virtual void calculateVertices() = 0;

            void updateVertex(){
                if(_mesh.geometryDirty){
                    _glMesh.upload(_mesh);
                    _mesh.geometryDirty = false;
                }
            }

            void setDeformable(bool deformable){
                if(deformable) {
                    _mesh.usage = render::types::MeshUsage::DYNAMIC;
                    return;
                }
                _mesh.usage = render::types::MeshUsage::STATIC;
                _mesh.geometryDirty = true;
            }          

            void setPosition(const BitMth::linalg::Vec2<float>& newPos) { _transform.position = newPos; }
            void setAngle(float angle)                                  { _transform.angle = angle; }  
            void setColor(const ::EasySDL::types::Color<float>& color)  { _material.color = color; }
            void setScale(const BitMth::linalg::Vec2<float>& newSca)    { _transform.scale = newSca; }

            [[nodiscard]] const BitMth::linalg::Vec2<float>& getPosition()const { return _transform.position; }
            [[nodiscard]] const BitMth::linalg::Vec2<float>& getScale()   const { return _transform.scale; }
            [[nodiscard]] const render::Transform2D<float>& getTransform()const { return _transform; }
            [[nodiscard]] const render::Material2D<float>& getMaterial()  const { return _material; }
            [[nodiscard]] const render::gl::GLMesh2D<float>& getGLMesh()  const { return _glMesh; }
            [[nodiscard]] const render::Mesh2D<float>& getMesh()          const { return _mesh; }
            [[nodiscard]] float getAngle()                                const noexcept { return _transform.angle; }

            [[nodiscard]] render::Mesh2D<float>& getMesh()           { return _mesh; }
            [[nodiscard]] BitMth::linalg::Vec2<float>& getPosition() { return _transform.position; }
            [[nodiscard]] BitMth::linalg::Vec2<float>& getScale()    { return _transform.scale; }
            [[nodiscard]] render::Transform2D<float>& getTransform() { return _transform; }
            [[nodiscard]] render::Material2D<float>& getMaterial()   { return _material; }
            [[nodiscard]] render::gl::GLMesh2D<float>& getGLMesh()   { return _glMesh; }

       

            // std::string getAngleStr(){
            //     char buf[32];
            //     std::snprintf(buf, sizeof(buf),"%.2f",this->_angle);
            //     std::string angleStr(buf);
            //     return angleStr;
            // }
            // std::string getAngleDegStr(){
            //     char buf[32];
            //     float degAngle = this->_angle *(180/M_PI);
            //     std::snprintf(buf, sizeof(buf),"%.1f",degAngle);
            //     std::string angleStr(buf);
            //     return angleStr;
            // }
    };
}