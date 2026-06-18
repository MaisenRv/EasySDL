#pragma once

#include <EasySDL/types/Color.hpp>

namespace EasySDL::render{
    template <typename T>
    struct Material2D{
        ::EasySDL::types::Color<T> color; 
        T lineWidth = T(1);

        explicit Material2D(const ::EasySDL::types::Color<T>& color):color(color){}

        Material2D() = default;
        Material2D(const Material2D& material) = default;
        Material2D( Material2D&& material) noexcept = default;
        Material2D& operator=( const Material2D& material) = default;
        Material2D& operator=( Material2D&& material) noexcept = default;
        ~Material2D() = default;
    };
}