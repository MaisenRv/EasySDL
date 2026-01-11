#include "../../include/EasySDL/WindowLocal.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/objects/shape/square/RoundedRectangle.hpp"

EasySDL::WindowLocal *w = new EasySDL::WindowLocal(600, 600, "WindowName");
EasySDL::RoundedRectagle r({300,300},100,50,10,9);
void setup(){
  r.setup();
  r.setDeformable(false);
};

float t = 0;
void draw(){
    r.setPos({
        w->getMouseState().x,
        w->getHeight() - w->getMouseState().y
    });
    if(w->getMouseState().leftDown){
        r.setColor(EasySDL::RED_PINKY_NORMALIZED);
    }else if(w->getMouseState().rightDown){
        r.setColor(EasySDL::LIGHT_CYAN_NORMALIZED);
    }else{
        r.setColor(EasySDL::WHITE_NORMALIZED);
    }

    r.draw(w);
}


int main(){
   
    w->start(draw, setup);
}