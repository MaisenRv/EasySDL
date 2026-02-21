#pragma once
#include "Mesh2D.hpp"
#include "../../types/LineAttachmentTypes.hpp"
#include "../../../Math/types/Vec2.hpp"

namespace EasySDL
{
    template <typename T = float>
    class Geometry2D
    {
    private:
        static void _calculateCornerRoundedRectangle(Mesh2D<T>& mesh, Math::Vec2 dimention,float delta, int cornerNumberVertex, float radius,int quadrant){
            Math::Vec2 quadrantV = {0,0};
            float angle = 0;
            float end = float(M_PI_2);

            if(quadrant == 1) quadrantV = {1,-1};
            else if (quadrant == 2) {
                quadrantV = {-1,-1};
                angle = float(M_PI_2);
                end = -float(M_PI);
            }
            else if (quadrant == 3) {
                quadrantV = {-1,1};
                angle = -float(M_PI);
                end = -float(M_PI_2);
            }
            else{
                quadrantV = {1,1};
                angle = -float(M_PI_2);   
                end = 0;
            }

            float x_ = (dimention.x) * quadrantV.x;
            float y_ = (dimention.y) * quadrantV.y;

            for (size_t i = 0; i <= cornerNumberVertex; i++)
            {
                mesh.addPoint(
                    x_ + (radius * std::cos(angle)),
                    y_ - (radius * std::sin(angle))
                );
                angle += delta;
            }
            mesh.addPoint(
                x_ + (radius * std::cos(end)),
                y_ - (radius * std::sin(end))
            );
            
            if(quadrant == 4){
                mesh.addPoint(
                    x_ + (radius * std::cos(end)),
                    -y_ - (radius * std::sin(end))
                );
            }
        }
    public:
        static void buildCircle(Mesh2D<T>& mesh, float radius, int segments){
            mesh.clear();
            mesh.addPoint(0.0f,0.0f);

            float delta = (2.0f * float(M_PI)) / segments;
            for (size_t i = 0; i <= segments; i++)
            {
                float angle = i * delta;
                mesh.addPoint(
                    radius * std::cos(angle), // X
                    radius * std::sin(angle)  // Y
                );
            }
        }

        static void buildSquare(Mesh2D<T>& mesh, float width, float height){
            mesh.clear();
            mesh.addPoint(0.0f,0.0f);
            float hWidth = width / 2;
            float hHeight = height / 2;

            mesh.addPoint(hWidth,hHeight);
            mesh.addPoint(-hWidth,hHeight);
            mesh.addPoint(-hWidth,-hHeight);
            mesh.addPoint(hWidth,-hHeight);
            mesh.addPoint(hWidth,hHeight);
        }

        static void buildRoundedRectangle(Mesh2D<T>& mesh, float width, float height, float radius, int resolution){
            mesh.clear();
            mesh.addPoint(0.0f,0.0f);
            float hWidth = width / 2;
            float hHeight = height / 2;

            if(resolution % 4 != 0){
                resolution += 4 - (resolution % 4);
            }
            int cornerNumberVertex = (int)(resolution / 4) + 1;
            float cornerDelta = float(M_PI_2) / cornerNumberVertex;

            for (size_t i = 1; i < 5; i++){
                Geometry2D<T>::_calculateCornerRoundedRectangle(
                    mesh,
                    {hWidth,hHeight},
                    cornerDelta,
                    cornerNumberVertex,
                    radius,
                    i
                );
            }
            
        }

        static void buildLine(Mesh2D<T>& mesh, LineAttachmentTypes type){
            mesh.clear();
            if(type == LineAttachmentTypes::ATTACH_P0){
                mesh.addPoint(0.0f,0.0f);
                mesh.addPoint(1.0f,0.0f);
                return;
            }
            if(type == LineAttachmentTypes::ATTACH_P1){
                mesh.addPoint(-1.0f,0.0f);
                mesh.addPoint(0.0f,0.0f);
                return;
            }
            if(type == LineAttachmentTypes::ATTACH_CENTER){
                mesh.addPoint(-0.5f,0.0f);
                mesh.addPoint(0.5f,0.0f);
                return;
            }
        }
    }; 
} 
