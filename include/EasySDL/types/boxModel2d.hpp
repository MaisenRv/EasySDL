#pragma once
#include "../../Math/types/Vec2.hpp"

namespace EasySDL
{
    enum class PositionType {Center, TopLeft, BottomLeft};
    struct BoxModel2d
    {
        PositionType type = PositionType::BottomLeft;
        Math::Vec2* position = nullptr;
        float width = 0;
        float height = 0;  
    };
}
