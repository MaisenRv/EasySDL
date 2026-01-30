#pragma once 
#include "../types/boxModel2d.hpp"

namespace EasySDL{
    class ICollitionObject{
        protected:
            BoxModel2d boxModel;
            bool isActivateCollitions = false;
            bool isColliding = false;

        public:
            virtual ~ICollitionObject() = default;
            virtual bool IsColliding(Math::Vec2 objectPosition) = 0;
            virtual void updateBoxModel() = 0;
            bool getIsActivateCollitions(){
                return this->isActivateCollitions;
            };
            void setIsActivateCollitions(bool activateCollitions){
                this->isActivateCollitions = activateCollitions;
            }
    };
}