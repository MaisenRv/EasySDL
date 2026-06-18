#pragma once

#include <EasySDL/interface/IWindow.hpp>

namespace EasySDL {
    class Window;
    class WindowLocal;
}

namespace EasySDL::render {
    class Renderer2D;
}

namespace EasySDL{    
    class IDrawable{
        public:
            virtual ~IDrawable() = default;
            virtual void render(render::Renderer2D& renderer,EasySDL::IWindow *w) = 0;

        protected:
            IDrawable() = default;
    };
}

