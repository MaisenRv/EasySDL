#pragma once

#include "../../interface/IDrawable.hpp"
#include "../../interface/IInitializable.hpp"
#include "../../../Math/types/Vec2.hpp"
#include "../../render/core/Transform2D.hpp"
#include "../../render/core/Material2D.hpp"
#include "../../render/geometry/Mesh2D.hpp"
#include "../../render/opengl/GLMesh2D.hpp"
#include "../../render/shaders/ShapeShader2D.hpp"

#include <GL/glew.h>

namespace EasySDL{
    class Shape : public EasySDL::IDrawable, public EasySDL::IInitializable {
        protected:
            Transform2D _transform;
            Material2D _material;
            Mesh2D<float> _mesh;
            GLMesh2D<float> _glMesh;

            void _onSetup() override{
                this->calculateVertices();
                this->_glMesh.create();
                this->updateVertex(); 
            }

        public:

            ~Shape(){
                this->_glMesh.del();
            };
            Shape(const Math::Vec2 position):_transform(position){}
            virtual void calculateVertices() = 0;

            void updateVertex(){
                if(this->_mesh.geometryDirty){
                    this->_glMesh.upload(this->_mesh);
                    this->_mesh.geometryDirty = false;
                }
            }

            void setDeformable(bool deformable){
                if(deformable) {
                    this->_mesh.usage = MeshUsage::DYNAMIC;
                    return;
                }
                this->_mesh.usage = MeshUsage::STATIC;
                this->_mesh.geometryDirty = true;
            }            
            void setPosition(const Math::Vec2 newPos){ this->_transform.position = newPos; }
            void setAngle(float angle)               { this->_transform.angle = angle; }  
            void setColor(const Color color)         { this->_material.color = color; }
            void setScale(const Math::Vec2 newSca)   { this->_transform.scale = newSca; }

            const Math::Vec2 getPosition()     const { return this->_transform.position; }
            const float getAngle()             const { return this->_transform.angle; }
            const Math::Vec2 getScale()        const { return this->_transform.scale; }
            const Transform2D& getTransform()  const { return this->_transform; }
            const Material2D& getMaterial()    const { return this->_material; }
            const GLMesh2D<float>& getGLMesh() const { return this->_glMesh; }
            const Mesh2D<float>& getMesh()     const { return this->_mesh; }

       

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