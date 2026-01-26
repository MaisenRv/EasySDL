#pragma once 
#include "../types/boxModel2d.hpp"
#include "../../Math/types/Vec2.hpp"
#include <iostream>
namespace EasySDL{
    class Collitions{
        public:
        static bool calculateSquareCollition(EasySDL::Vec2 objectPosition,BoxModel2d* model){
            if(model->type == EasySDL::PositionType::Center){
                float halfWidth = model->width / 2;
                float halfHeight = model->height / 2;
                if(objectPosition.x < model->position->x - halfWidth) return false;
                if(objectPosition.x > model->position->x + halfWidth) return false;
                if(objectPosition.y < model->position->y - halfHeight) return false;
                if(objectPosition.y > model->position->y + halfHeight) return false;
                return true;   
            }
            return false;
        }
    };
}