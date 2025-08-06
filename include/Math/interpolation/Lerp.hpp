#pragma once
#include "../types/Vec2.hpp"
#include <iostream>

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
            static Vec2 lerp(const Vec2 pos1, const Vec2 pos2, const float t) {
                if(_checkT(t)) return {0,0};

                return pos1 + ( (pos2 - pos1) * t );
            }

            static float lerpAngle(const float angle0 ,const float angle1, const float t) {
                if(_checkT(t)) return 0;

                return angle0 + (angle1 - angle0) * t;
            } 
    };
}