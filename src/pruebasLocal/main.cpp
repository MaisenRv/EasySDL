#include "../../include/EasySDL/WindowLocal.hpp"

#include "../../include/EasySDL/objects/shape/particle/Particle.hpp"
#include "../../include/EasySDL/objects/shape/line/Line.hpp"

EasySDL::WindowLocal *w = new EasySDL::WindowLocal(600, 600, "WindowName");
int resolution = 40;
EasySDL::Particle p(300,325,5,resolution);
EasySDL::Line l(300,250,300,400,2);

float t = 0;

void setup(){
    p.setup();
    l.setup();
};

void draw(){
    t+=0.04f;
    l.setAngle(t);
    p.draw(w);
    l.draw(w);
    
    
}


int main(){
   
    w->start(draw, setup);
}