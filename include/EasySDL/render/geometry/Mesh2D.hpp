#pragma once

#include <vector>

#include <EasySDL/render/types/PrimitiveTypes.hpp>
#include <EasySDL/render/types/MeshUsage.hpp>
#include <BitMth/linalg/Vec2.hpp>

namespace EasySDL::render{
    template <typename T>
    struct Mesh2D {
        std::vector<BitMth::linalg::Vec2<T>> vertices;
        bool geometryDirty = true;
        types::MeshUsage usage = types::MeshUsage::STATIC;
        types::PrimitiveType primitiveType = types::PrimitiveType::TriangleFan;
        
        Mesh2D() = default;
        Mesh2D(const Mesh2D& mesh) = default;
        Mesh2D( Mesh2D&& mesh) noexcept = default;
        Mesh2D& operator=( const Mesh2D& mesh) = default;
        Mesh2D& operator=( Mesh2D&& mesh) noexcept = default;
        ~Mesh2D() = default;

        // void clear(){ 
        //     vertices.clear();
        //     geometryDirty = true;
        // }

        [[nodiscard]] const size_t vertexCount() const noexcept { return vertices.size(); }

        // void addPoint(T x, T y){
        //     vertices.push_back(x);
        //     vertices.push_back(y);
        //     geometryDirty = true;
        // }
        
        // void removeFirstPoint()
        // {
        //     if (!vertices.empty())
        //     {
        //         vertices.erase(vertices.begin());
        //         vertices.erase(vertices.begin());
        //         geometryDirty = true;
        //     }
        // }
    };
}




