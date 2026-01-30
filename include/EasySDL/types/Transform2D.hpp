#pragma once
#include "../../Math/types/Vec2.hpp"

namespace EasySDL
{
    struct Transform2D
    {
        Math::Vec2 position;
        Math::Vec2 scale = {1.0f,1.0f};
        float angle = 0.0f;
        Transform2D(const Math::Vec2 &pos):position(pos){}
    };
}
