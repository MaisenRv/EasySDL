
#include "../../include/EasySDL/Window.hpp"
#include "../../include/EasySDL/objects/shape/particle/Particle.hpp"
#include "../../include/EasySDL/objects/shape/line/ConstraintLine.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/Math/models/Pendulum.hpp"
#include <cmath>


EasySDL::Window *w = new EasySDL::Window(400, 400, "Pendulum");
EasySDL::Particle point(200, 200, 5, 50);
EasySDL::ContraintLine line(200, 200, 200, 200, 2, 175);
EasySDL::Particle pMass(200, 50, 20, 50);
Math::Pendulum pendulum(line.getAngle(),0,0,line.getLength(),0.0111);

void setup(){
    point.setup();
    pMass.setColor(EasySDL::RED_PINKY_NORMALIZED);
    pMass.setup();
    line.setAngle(M_PI_2+M_PI_4);
    pendulum.setAngle(line.getAngle());
    line.setup();
}

void draw(){
    line.draw(w);
    point.draw(w);
    pMass.draw(w);
    float angle = pendulum.calculateAngleNextIteration();
    line.setAngle(angle);
    pMass.setPos(line.getPosPoint2());
}

int main(){
    w->start(draw,setup);
}