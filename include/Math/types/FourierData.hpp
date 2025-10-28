#pragma once
#include "Complex.hpp"
namespace EasySDL
{
    struct FourierData
    {
        Complex numbers;
        float frecuency;
        float amplitude;
        float phase;
    };
}