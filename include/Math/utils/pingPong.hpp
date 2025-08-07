
#include <cmath>
namespace EasySDL
{
    float pingPongDown(float time, float min, float max){
        float range = max - min;
        float mod = fmod(time - min, 2.0f * range);
        return min + fabs(mod - range);
    }

    float pingPongUp(float time, float min, float max) {
        float length = max - min;
        float mod = std::fmod(time, 2.0f * length);
        return min + (length - std::fabs(mod - length));
    }
}