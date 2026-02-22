#pragma once

#include "FontShape.hpp"
#include "../../render/Renderer2D.hpp"

namespace EasySDL
{
    class Text : public FontShape
    {
        public:
            Text(const std::string &fontPath, int fontSize):FontShape(fontPath,fontSize){}
            void render(Renderer2D& renderer,EasySDL::IWindow *w) override{
                renderer.draw(w,*this);
            }
    };
}
