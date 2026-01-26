#include "../../include/EasySDL/WindowLocal.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/objects/shape/square/RoundedRectangle.hpp"
#include "../../include/EasySDL/objects/button/Button.hpp"

EasySDL::WindowLocal *w = new EasySDL::WindowLocal(600, 600, "WindowName");
EasySDL::Button b({0,300},120,40,5,8,"boton");
void setup(){
    b.setDeformable(false);
    b.setColor(EasySDL::MINT_GREEN_NORMALIZED);
    b.setIsActivateCollitions(true);
    b.setActivateHover(true);
    b.setup();
};

float t = 0;
float deltaT = 2;
void draw(){
    if(b.IsColliding({w->getMouseState().x,w->getMouseState().y})){
        b.setColor(EasySDL::RED_PINKY_NORMALIZED);
    }else{
        b.setColor(EasySDL::MINT_GREEN_NORMALIZED);
    }

    if(t > 500 && deltaT > 0 || t < 100 && deltaT < 0){
        deltaT *= -1;
    }
    t += deltaT;
    b.setPos({t,300});
    b.hoverScaleAnimation(0.05,2);
    b.draw(w);
}


int main(){
   
    w->start(draw, setup);
}