#pragma once
#include "./shaders/ShapeShader2D.hpp"
#include "./shaders/FontShader.hpp"
#include "./../interface/IWindow.hpp"
#include "./../objects/shape/shape.hpp"
#include "./../objects/text/FontShape.hpp"

namespace EasySDL{

    class Renderer2D
    {
    private:
        ShapeShader2D _shapeShader;
        FontShader _fontShader;

        GLenum toGL(PrimitiveType type) {
            switch(type) {
                case PrimitiveType::Lines: return GL_LINES;
                case PrimitiveType::LineStrip: return GL_LINE_STRIP;
                case PrimitiveType::Triangles: return GL_TRIANGLES;
                case PrimitiveType::TriangleFan: return GL_TRIANGLE_FAN;
                case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
            }
            return GL_TRIANGLES;
        }
    public:
        void init(){
            this->_shapeShader.init();
            this->_fontShader.init();
        }

        void draw(IWindow *w, Shape &shape){
            if(shape.getMesh().geometryDirty){
                shape.calculateVertices();
            }
            shape.updateVertex();
        
            this->_shapeShader.use();
            this->_shapeShader.updateUniforms(w,shape.getTransform(),shape.getMaterial());

            glBindVertexArray(shape.getGLMesh().VAO);
            if(shape.getMesh().primitiveType == PrimitiveType::Lines || shape.getMesh().primitiveType == PrimitiveType::LineStrip){
                glLineWidth(shape.getMaterial().lineWidth);
            }
            glDrawArrays(this->toGL(shape.getMesh().primitiveType), 0, shape.getMesh().vertexCount());
            glBindVertexArray(0);  
        }
        void draw(IWindow *w, FontShape &fontShape){
            if(fontShape.getMaterial().textureDirty){
                fontShape.generateTexture();
            }
            if(fontShape.getMesh().geometryDirty){
                fontShape.calculateVertices();
            }
    
            fontShape.updateVertex();
            this->_fontShader.use();
            this->_fontShader.updateUniforms(w,fontShape.getTransform(),fontShape.getMaterial());
            glBindVertexArray(fontShape.getGLMesh().VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        

        ~Renderer2D(){
            this->_shapeShader.del();
            this->_fontShader.del();
        }
    };
    
}