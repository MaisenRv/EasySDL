#pragma once

namespace Math{
    float EulerMethod( float y0 ,float step, float &t, float F){
        t += step;
        float y = y0 + step * F;
        return y;
    }

    void EulerMethod2Order( float &y0 ,float &y1, float step, float &t, float F){
        t += step;
        y0 += step * F;
        y1 += step * y0;
    }


}