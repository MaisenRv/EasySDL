#pragma once
#include "../../types/PrimitiveTypes.hpp"

#include <vector>

namespace EasySDL{

    enum class MeshUsage{
        STATIC,
        DYNAMIC
    };


    template <typename T = float>
    struct Mesh2D
    {
        std::vector<T> vertices;
        bool geometryDirty = false;
        MeshUsage usage = MeshUsage::STATIC;
        PrimitiveType primitiveType = PrimitiveType::TriangleFan;
        
        void clear(){ 
            vertices.clear();
            geometryDirty = true;
        }

        const int vertexCount() const{
            return vertices.size() / 2;
        }

        void addPoint(T x, T y){
            vertices.push_back(x);
            vertices.push_back(y);
            geometryDirty = true;
        }
    };
}




