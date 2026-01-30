#pragma once
#include "../shape/square/RoundedRectangle.hpp"
#include "../../interface/ICollitionObject.hpp"
#include "../text/Text.hpp"
#include "../../utils/fonts.hpp"
#include "../../utils/collitions.hpp"
#include "../../../Math/interpolation/Quadratic.hpp"

namespace EasySDL
{
    class Button : public EasySDL::RoundedRectagle, public EasySDL::ICollitionObject{
        private:
        EasySDL::Text _text;
        float _textScale;
        bool _isHoverActivate = false;

        float _hoverAnimationTime = 0;

        bool _wasPressed = false;

        public:
        Button(Math::Vec2 position,float width,float height, float radius, int resolution,std::string text):
            EasySDL::RoundedRectagle(position,width,height,radius,resolution),
            _text(EasySDL::POPPINS_REGULAR, 64)
            {
                this->boxModel.height = this->_height + (2*this->_radius);
                this->boxModel.width = this->_width + (2*this->_radius);
                this->boxModel.position = &(this->_position);
                this->boxModel.type = EasySDL::PositionType::Center;

                this->_text.setPos(this->getPosition());
                this->_textScale = (height*3)/400.0f;
                this->_text.setScale(this->_textScale);
                this->_text.setMessage(text);
            }

        void draw(EasySDL::IWindow *w) override{
            EasySDL::RoundedRectagle::draw(w);
            this->_text.draw(w);
        }
        void updateBoxModel() override{
            float border = 2 * this->_radius;
            this->boxModel.height = this->_scale.y * (this->_height + border);
            this->boxModel.width = this->_scale.x * (this->_width + border);
        }

        void hoverScaleAnimation(float deltaT, float finalScale){
            if(!this->_isHoverActivate) return;

            if(this->isColliding && this->_hoverAnimationTime < 1){
                this->_hoverAnimationTime += deltaT;
            }
            if(!this->isColliding && this->_hoverAnimationTime > 0){
                this->_hoverAnimationTime -= deltaT;
            }
            
            if(this->_hoverAnimationTime > 1){
                this->_hoverAnimationTime = 1;
            }
            if(this->_hoverAnimationTime < 0){
                this->_hoverAnimationTime = 0;
            }
            float newScale = EasySDL::Quadratic::quadratic(1,finalScale,this->_hoverAnimationTime,EasySDL::Quadratic::TypeQuadraticInterpolation::easeInOut);
            this->setScale(newScale);
        }

        bool IsColliding(Math::Vec2 objectPosition) override{
            if(!this->isActivateCollitions)
                return false;

            this->isColliding = EasySDL::Collitions::calculateSquareCollition(objectPosition,&(this->boxModel));
            return this->isColliding;
        }

        void executeClickEvent(bool isPressed, std::function<void()> clickEvent){
           if (isPressed && !_wasPressed) {
                clickEvent(); 
            }
            _wasPressed = isPressed;
        }

        void setScale(Math::Vec2 scale) override{
            EasySDL::RoundedRectagle::setScale(scale);
            this->_text.setScale((this->_height * 3 * scale.y)/400.0f);
            this->updateBoxModel();
        }
        void setScale(float scale) override{
            EasySDL::RoundedRectagle::setScale(scale);
            this->_text.setScale((this->_height * 3 * scale)/400.0f);
            this->updateBoxModel();
        }

        float getTextScale(){
            return this->_textScale;
        }

        void setActivateHover(bool hover){
            this->_isHoverActivate = hover;
        }

        void setPos(const Math::Vec2 newPos) override{
            EasySDL::RoundedRectagle::setPos(newPos);
            this->_text.setPos(newPos);
        }

        void setText(std::string text){
            this->_text.setMessage(text);
        }
    };
}