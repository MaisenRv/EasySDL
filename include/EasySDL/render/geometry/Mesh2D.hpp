#pragma once
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
        int vertexCount = 0;
        bool geometryDirty = false;
        MeshUsage usage = MeshUsage::STATIC;
        
        void clear(){ 
            vertices.clear();
            geometryDirty = true;
        }

        void updateVertexCount(){
            vertexCount = vertices.size() / 2;
        }

        void addPoint(T x, T y){
            vertices.push_back(x);
            vertices.push_back(y);
            geometryDirty = true;
        }
    };
}




