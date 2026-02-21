#pragma once
#include "IWindow.hpp"

namespace EasySDL{
    class Window;
    class WindowLocal;
    class Renderer2D;
    
    class IDrawable{
        public:
            virtual ~IDrawable() = default;
            virtual void render(Renderer2D& renderer,EasySDL::IWindow *w) = 0;
    };
}

