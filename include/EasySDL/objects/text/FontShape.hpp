#pragma once

#include "../../interface/IDrawable.hpp"
#include "../../interface/IInitializable.hpp"
#include "../../render/opengl/GLFontMesh.hpp"
#include "../../render/core/MaterialFont.hpp"
#include "../../render/core/Transform2D.hpp"
#include "../../render/geometry/Mesh2D.hpp"
#include "../../types/FontType.hpp"

#include <string>

namespace EasySDL
{
    class FontShape : public IDrawable, public IInitializable
    {
    protected:
        GLFontMesh<float> _glFontMesh;
        MaterialFont _material;
        Transform2D _transform;
        Mesh2D<float> _mesh;
        FontType _fontType;
        int _wText, _hText;
        
        std::string _message = "";
        
        void _onSetup() override{
            this->calculateVertices();
            this->_glFontMesh.create();
            this->updateVertex(); 
        }

        void _createTexture(){
            glGenTextures(1, &(this->_material.textTexture));
            glBindTexture(GL_TEXTURE_2D, this->_material.textTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

    public:
        FontShape(const std::string &fontPath, int fontSize)
            : _transform({0, 0}), _fontType(fontPath, fontSize) {
                this->_createTexture();
                this->_mesh.primitiveType = PrimitiveType::Triangles;
        }

        ~FontShape()
        {
            this->_glFontMesh.del();
            this->_material.del();
            this->_fontType.close();
        }
        void updateVertex(){
            if(this->_mesh.geometryDirty){
                this->_glFontMesh.upload(this->_mesh);
                this->_mesh.geometryDirty = false;
            }
        }

        void generateTexture()
        {
            SDL_Surface *surf = TTF_RenderText_Blended(
                this->_fontType.font,
                this->_message.c_str(),
                this->_material.color);

            if (!surf){
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Blended error: %s", TTF_GetError());
                return;
            }

            SDL_Surface *formatted = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_ABGR8888, 0);
            SDL_FreeSurface(surf);
            surf = formatted;

            this->_wText = surf->w;
            this->_hText = surf->h;

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glBindTexture(GL_TEXTURE_2D, this->_material.textTexture);
            glTexImage2D(
                GL_TEXTURE_2D,0,GL_RGBA,this->_wText,this->_hText,0,
                GL_RGBA,GL_UNSIGNED_BYTE,surf->pixels
            );
            glGenerateMipmap(GL_TEXTURE_2D);
            SDL_FreeSurface(surf);
            this->_material.textureDirty = false;
            this->_mesh.geometryDirty = true;
        }

        void calculateVertices(){
            this->_mesh.clear();
            float w = float(this->_wText);
            float h = float(this->_hText);

            this->_mesh.addPoint(-w, h);
            this->_mesh.addPoint(0.0f, 0.0f);
            this->_mesh.addPoint(w, h);
            this->_mesh.addPoint(1.0f, 0.0f);
            this->_mesh.addPoint(w, -h);
            this->_mesh.addPoint(1.0f, 1.0f);
            this->_mesh.addPoint(-w, -h);
            this->_mesh.addPoint(0.0f, 1.0f);
        }
        
        void setMessage(const std::string &message)
        {
            this->_message = message;
            this->_material.textureDirty = true;
        }

        int getwText(){ return this->_wText; }
        int gethText(){ return this->_hText; }
       
        void setPosition(const Math::Vec2 newPos){ this->_transform.position = newPos; }
        void setAngle(float angle)               { this->_transform.angle = angle; }  
        void setColor(const SDL_Color color)     { this->_material.color = color; }
        void setScale(const Math::Vec2 newSca)   { this->_transform.scale = newSca; }

        const Math::Vec2 getPosition()       const { return this->_transform.position; }
        const float getAngle()               const { return this->_transform.angle; }
        const Math::Vec2 getScale()          const { return this->_transform.scale; }
        const Transform2D& getTransform()    const { return this->_transform; }
        const MaterialFont& getMaterial()    const { return this->_material; }
        const GLFontMesh<float>& getGLMesh() const { return this->_glFontMesh; }
        const Mesh2D<float>& getMesh()       const { return this->_mesh; }
    };
}