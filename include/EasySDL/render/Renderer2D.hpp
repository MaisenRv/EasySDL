#pragma once

#include <EasySDL/render/shaders/ShapeShader2D.hpp>
// #include "./shaders/FontShader.hpp"
// #include "./../objects/text/FontShape.hpp"

#include <EasySDL/interface/IWindow.hpp>
#include <EasySDL/objects/shape/Shape.hpp>

namespace EasySDL::render{
    class Renderer2D{
    private:
        ShapeShader2D _shapeShader;
        // FontShader _fontShader;

        GLenum toGL(types::PrimitiveType type) {
            switch(type) {
                case types::PrimitiveType::Lines: return GL_LINES;
                case types::PrimitiveType::LineStrip: return GL_LINE_STRIP;
                case types::PrimitiveType::Triangles: return GL_TRIANGLES;
                case types::PrimitiveType::TriangleFan: return GL_TRIANGLE_FAN;
                case types::PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
            }
            return GL_TRIANGLES;
        }
    public:
        void init(){
            this->_shapeShader.init();
            // this->_fontShader.init();
        }

        void draw(IWindow *w, objects::Shape &shape){
            if(shape.getMesh().geometryDirty){
                shape.calculateVertices();
            }
            shape.updateVertex();
        
            this->_shapeShader.use();
            this->_shapeShader.updateUniforms(w,shape.getTransform(),shape.getMaterial());

            glBindVertexArray(shape.getGLMesh().VAO);
            if(shape.getMesh().primitiveType == types::PrimitiveType::Lines || shape.getMesh().primitiveType == types::PrimitiveType::LineStrip){
                glLineWidth(shape.getMaterial().lineWidth);
            }
            glDrawArrays(this->toGL(shape.getMesh().primitiveType), 0, shape.getMesh().vertexCount());
            glBindVertexArray(0);  
        }
        
        // void draw(IWindow *w, FontShape &fontShape){
        //     if(fontShape.getMaterial().textureDirty){
        //         fontShape.generateTexture();
        //     }
        //     if(fontShape.getMesh().geometryDirty){
        //         fontShape.calculateVertices();
        //     }
    
        //     fontShape.updateVertex();
        //     this->_fontShader.use();
        //     this->_fontShader.updateUniforms(w,fontShape.getTransform(),fontShape.getMaterial());
        //     glBindVertexArray(fontShape.getGLMesh().VAO);
        //     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //     glBindVertexArray(0);
        // }

        

        ~Renderer2D(){
            // this->_fontShader.del();
        }
    };
    
}