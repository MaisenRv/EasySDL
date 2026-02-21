#include "../../include/EasySDL/WindowLocal.hpp"
#include "../../include/EasySDL/objects/shape/Square.hpp"
#include "../../include/EasySDL/objects/shape/RoundedRectangle.hpp"
#include "../../include/EasySDL/objects/shape/Line.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/render/Renderer2D.hpp"
#include "../../include/EasySDL/Scene.hpp"
#include "../../include/EasySDL/types/LineAttachmentTypes.hpp"

EasySDL::WindowLocal *w = new EasySDL::WindowLocal(600, 600, "WindowName");
EasySDL::Renderer2D renderer;
EasySDL::Scene scene;
EasySDL::Square c(100,100,20,20);
// EasySDL::RoundedRectagle rr(300,300,40,30,10,20);
EasySDL::Line l({300,300},{500,500},2);

void setup(){
    renderer.init();
    l.setLineAttachType(EasySDL::LineAttachmentTypes::ATTACH_P1);
    scene.addObject(c);
    // scene.addObject(rr);
    scene.addObject(l);
};

float t = 0;
float lados = 1;
float angle = 0;
void draw(){
    c.setPosition({100,100+t});
    if(static_cast<int>(t) % 30 == 0){
        lados+=0.1;
    }
    c.setScale({lados,lados});
    // rr.setScale({lados,lados});
    l.setAngle(angle);
    
    scene.render(renderer,w);
    t+=0.5;
    angle += 0.01;
}


int main(){
    w->start(draw, setup);
}