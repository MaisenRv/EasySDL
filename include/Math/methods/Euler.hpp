#pragma once

namespace Math{
    float EulerMethod( float y0 ,float step, float &t, float F){
        t += step;
        float y = y0 + step * F;
        return y;
    }


}