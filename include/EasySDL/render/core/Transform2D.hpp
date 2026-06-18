#pragma once

#include <BitMth/linalg/Vec2.hpp>

namespace EasySDL::render {
    template <typename T>
    struct Transform2D {
        BitMth::linalg::Vec2<T> position{};
        BitMth::linalg::Vec2<T> scale = {T(1),T(1)};
        T angle{};

        explicit Transform2D(const BitMth::linalg::Vec2<T>& pos):position(pos){}

        Transform2D() = default;
        Transform2D(const Transform2D& transform) = default;
        Transform2D( Transform2D&& transform) noexcept = default;
        Transform2D& operator=( const Transform2D& transform) = default;
        Transform2D& operator=( Transform2D&& transform) noexcept = default;
        ~Transform2D() = default;
    };
}
