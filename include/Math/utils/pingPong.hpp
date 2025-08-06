
#include <cmath>
namespace EasySDL
{
    float pingPong(float time, float min, float max){
        float range = max - min;
        float mod = fmod(time - min, 2.0f * range);
        return min + fabs(mod - range);
    }
}