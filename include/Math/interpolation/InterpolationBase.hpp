#pragma once
#include "../types/Vec2.hpp"
#include <iostream>
#include <functional>

namespace EasySDL
{
    class InterpolationBase{
        protected:
            static bool _checkT(const float t) {
                if(t < 0 || t > 1){
                    std::cerr << "Error: t must be between 0 and 1" << std::endl;
                    return true;
                }
                return false;
            }
            static float calBase(const float start, const float end,const float t,const std::function<float(float)> f){
                return start + ((end - start) * f(t) );
            }

            static Vec2 calBaseVec2(const Vec2 start, const Vec2 end,const float t,const std::function<float(float)> f){
                return start + ((end - start) * f(t) );
            }
    };
}