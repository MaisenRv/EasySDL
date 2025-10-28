#pragma once
#include "InterpolationBase.hpp"

namespace EasySDL
{
    class Lerp : public InterpolationBase{       
        public:
            static float lineal(float t){ return t;}

            static float lerp(const float start, const float end, const float t) {
                if(_checkT(t)) return 0;
                return calBase(start,end,t,lineal);
            }

            static Vec2 lerpVec2(const Vec2 pos1, const Vec2 pos2, const float t) {
                if(_checkT(t)) return {0,0};
                return calBaseVec2(pos1,pos2,t,lineal);
            }

            static float (&lerpColor(const float (&colorStart)[4], const float  (&colorEnd)[4], const float t ))[4]{
                static float result[4] = {0,0,0,0};
                if(_checkT(t)) return result;
                for (size_t i = 0; i < 4; i++) result[i] = lerp(colorStart[i],colorEnd[i],t);
                return result;
            }
    };
}