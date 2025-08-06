#pragma once
#include "../utils/Matrix.hpp"
#include "../types/Vec2.hpp"

#include <cmath>

namespace EasySDL
{   
    EasySDL::Vec2 rotate2D(EasySDL::Vec2 point, float angle, EasySDL::Vec2 center){
        EasySDL::Matrix<float> M = {
            {cosf(angle), -sinf(angle), center.x - center.x*cosf(angle) + center.y*sinf(angle)},
            {sinf(angle), cosf(angle) , center.y - center.x*sinf(angle) - center.y*cosf(angle)},
            {0          , 0           , 1}
        };
        EasySDL::Matrix<float> hv = {{point.x}, {point.y}, {1}};
        EasySDL::Matrix<float> result = M * hv;
        return {result[0][0], result[1][0]};
    }
}