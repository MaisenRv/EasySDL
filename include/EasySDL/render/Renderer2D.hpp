#pragma once
#include "./shaders/ShapeShader2D.hpp"
#include "./../interface/IWindow.hpp"
#include "./../objects/shape/shape.hpp"

namespace EasySDL{

    class Renderer2D
    {
    private:
        ShapeShader2D _shapeShader;

        GLenum toGL(PrimitiveType type) {
            switch(type) {
                case PrimitiveType::Lines: return GL_LINES;
                case PrimitiveType::Triangles: return GL_TRIANGLES;
                case PrimitiveType::TriangleFan: return GL_TRIANGLE_FAN;
                case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
            }
            return GL_TRIANGLES;
        }
    public:
        void init(){
            this->_shapeShader.init();
        }

        void draw(IWindow *w, Shape &shape){
            if(shape.getMesh().geometryDirty){
                shape.calculateVertices();
            }
            shape.updateVertex();
        
            this->_shapeShader.use();
            this->_shapeShader.updateUniforms(w,shape.getTransform(),shape.getMaterial());

            glBindVertexArray(shape.getGLMesh().VAO);
            if(shape.getMesh().primitiveType == PrimitiveType::Lines){
                glLineWidth(shape.getMaterial().lineWidth);
            }
            glDrawArrays(this->toGL(shape.getMesh().primitiveType), 0, shape.getMesh().vertexCount());  
        }

        ~Renderer2D(){
            this->_shapeShader.del();
        }
    };
    
}