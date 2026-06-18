#pragma once

namespace EasySDL::types{
    template <typename T>
    struct Color {
        T r = T(1);
        T g = T(1);
        T b = T(1);
        T a = T(1);
    };
}