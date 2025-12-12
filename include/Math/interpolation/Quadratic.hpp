#pragma once
#include "InterpolationBase.hpp"
#include <cmath>

namespace EasySDL
{
    class Quadratic: public InterpolationBase{
    public:
        enum TypeQuadraticInterpolation{
            easeIn,
            easeOut,
            easeInOut
        };

        static float easeInF(float t){ return t*t;}
        static float easeOutF(float t){ return 1- powf(1-t,2);}
        static float easeInOutF(float t){ 
            if (t < 0.5) return 2*t*t;
            else return 1 - 2 * powf(1-t,2);
        }

        static float quadratic(const float start, const float end, const float t, TypeQuadraticInterpolation type) {
            if(_checkT(t)) return 0;

            if     (type == TypeQuadraticInterpolation::easeIn)    return calBase(start,end,t,easeInF);
            else if(type == TypeQuadraticInterpolation::easeOut)   return calBase(start,end,t,easeOutF);
            else if(type == TypeQuadraticInterpolation::easeInOut) return calBase(start,end,t,easeInOutF);
            return calBase(start,end,t,easeInF);
        }

        static Vec2 quadratic(const Vec2 start, const Vec2 end, const float t, TypeQuadraticInterpolation type) {
            if(_checkT(t)) return {0,0};

            if     (type == TypeQuadraticInterpolation::easeIn)    return calBaseVec2(start,end,t,easeInF);
            else if(type == TypeQuadraticInterpolation::easeOut)   return calBaseVec2(start,end,t,easeOutF);
            else if(type == TypeQuadraticInterpolation::easeInOut) return calBaseVec2(start,end,t,easeInOutF);
            else return {0,0};
        }

        static float (&lerpColor(const float (&colorStart)[4], const float  (&colorEnd)[4], const float t, const TypeQuadraticInterpolation type))[4]{
            static float result[4] = {0,0,0,0};
            if(_checkT(t)) return result;
            for (size_t i = 0; i < 4; i++) result[i] = quadratic(colorStart[i],colorEnd[i],t, type);
            return result;
        }
    };    
}