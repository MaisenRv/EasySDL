#pragma once

namespace EasySDL{
    class Window;
    class IDrawable{
        public:
            virtual ~IDrawable() = default;
            virtual void draw(EasySDL::Window *w) = 0;
    };
}

