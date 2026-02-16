#pragma once
#include "Mesh2D.hpp"

namespace EasySDL
{
    template <typename T = float>
    class Geometry2D
    {
    public:
        static void buildCircle(Mesh2D<T>& mesh, float radius, int segments){
            mesh.clear();
            mesh.addPoint(0.0f,0.0f);

            float angle = 0;
            float delta = (2.0f * float(M_PI)) / segments;
            for (size_t i = 0; i <= this->_resolution; i++)
            {
                angle += delta;
                mesh.addPoint(
                    radius * std::cos(angle), // X
                    radius * std::sin(angle)  // Y
                ); 
            }
            mesh.updateVertexCount();
        }
    }; 
} 
