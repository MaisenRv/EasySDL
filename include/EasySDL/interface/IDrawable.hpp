#pragma once
#include "IWindow.hpp"

namespace EasySDL{
    class Window;
    class WindowLocal;
    
    class IDrawable{
        public:
            virtual ~IDrawable() = default;
            virtual void draw(EasySDL::IWindow *w) = 0;
    };
}

