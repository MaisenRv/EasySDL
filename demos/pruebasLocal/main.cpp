#include "../../include/EasySDL/WindowLocal.hpp"
// #include "../../include/EasySDL/objects/shape/Square.hpp"
// #include "../../include/EasySDL/objects/shape/RoundedRectangle.hpp"
// #include "../../include/EasySDL/objects/shape/Line.hpp"
#include "../../include/EasySDL/objects/shape/LineStrip.hpp"
#include "../../include/EasySDL/objects/text/Text.hpp"
#include "../../include/EasySDL/utils/fontsPath.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/utils/format.hpp"
#include "../../include/EasySDL/render/Renderer2D.hpp"
#include "../../include/EasySDL/Scene.hpp"
#include "../../include/EasySDL/types/LineAttachmentTypes.hpp"


EasySDL::WindowLocal *w = new EasySDL::WindowLocal(600, 600, "WindowName");
EasySDL::Renderer2D renderer;
EasySDL::Scene scene;
EasySDL::Text f(EasySDL::POPPINS_REGULAR,64);
// EasySDL::LineStrip ls(1);
// EasySDL::Square c(100,100,20,20);
// EasySDL::RoundedRectagle rr(300,300,40,30,10,20);
// EasySDL::Line l({200,200},0.3,100,1);

void setup(){
    renderer.init();
    f.setMessage("hola");
    f.setScale({0.15,0.15});
    f.setPosition({300,300});
    f.setAngle(1.5);
    scene.addObject(f);

    // l.setLineAttachType(EasySDL::LineAttachmentTypes::ATTACH_P0);
    // scene.addObject(c);
    // scene.addObject(rr);
    // scene.addObject(l);
    // ls.addPoint({100,100});
    // ls.addPoint({200,100});
    // ls.addPoint({100,200});
    // ls.addPoint({100,100});
    // scene.addObject(ls);
};

float t = 0;
float lados = 1;
float angle = 0;
void draw(){
    f.setMessage(EasySDL::floatFormat(t,2));
    // c.setPosition({100,100+t});
    // if(static_cast<int>(t) % 5 == 0){
    //     lados+=0.01;
    // }
    // c.setScale({lados,lados});
    // rr.setScale({lados,lados});
    // l.setAngle(angle);
    
    scene.render(renderer,w);
    t+=1;
    // angle += 0.01;
}


int main(){
    w->start(draw, setup);
}