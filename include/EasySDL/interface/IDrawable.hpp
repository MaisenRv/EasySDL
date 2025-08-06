#pragma once
#include "../Window.hpp"

namespace EasySDL{
    class IDrawable{
        public:
            virtual ~IDrawable() = default;
            virtual void draw(EasySDL::Window *w) = 0;
    };
}

