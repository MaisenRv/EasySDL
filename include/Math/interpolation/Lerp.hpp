#pragma once
#include "../types/Vec2.hpp"
#include <iostream>
#include <array>

namespace EasySDL
{
    class Lerp{
        private:
            static bool _checkT(const float t) {
                if(t < 0 || t > 1){
                    std::cerr << "Error: t must be between 0 and 1" << std::endl;
                    return true;
                }
                return false;
            }
        public:
            static float lerp(const float start, const float end, const float t) {
                if(_checkT(t)) return 0;
                return start + ( (end - start) * t );
            }
            static Vec2 lerpVec2(const Vec2 pos1, const Vec2 pos2, const float t) {
                if(_checkT(t)) return {0,0};
                return pos1 + ( (pos2 - pos1) * t );
            }

            // static float lerpAngle(const float angle0 ,const float angle1, const float t) {
            //     if(_checkT(t)) return 0;
            //     return angle0 + (angle1 - angle0) * t;
            // } 

            static float (&lerpColor(const float (&colorStart)[4], const float  (&colorEnd)[4], const float t ))[4]{
                static float result[4] = {0,0,0,0};
                if(_checkT(t)) return result;
                for (size_t i = 0; i < 4; i++) result[i] = lerp(colorStart[i],colorEnd[i],t);
                return result;
            }
    };
}