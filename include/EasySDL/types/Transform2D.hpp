#pragma once
#include "../../Math/types/Vec2.hpp"

namespace EasySDL
{
    struct Transform2D
    {
        Math::Vec2 position = {0,0};
        Math::Vec2 scale = {0,0};
        float rotación = 0.0f;
    };
}
