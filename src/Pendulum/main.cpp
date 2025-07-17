
#include "../../include/EasySDL/Window.hpp"
#include "../../include/EasySDL/objects/particle/Particle.hpp"
#include "../../include/EasySDL/objects/line/ConstraintLine.hpp"
#include "../../include/EasySDL/objects/text/Text.hpp"
#include "../../include/EasySDL/utils/pathList.hpp"

#include "../../include/Math/models/Pendulum.hpp"


EasySDL::Window *w = new EasySDL::Window(500, 500, "Pendulum");
EasySDL::Particle point(250, 250, 5, 50);
EasySDL::ContraintLine line(250, 250, 200, 200, 2, 200);
EasySDL::Particle pMass(250, 50, 20, 50);
EasySDL::Text infoAngle(EasySDL::POPPINS_REGULAR, 72);
EasySDL::Text infoVel(EasySDL::POPPINS_REGULAR, 72);
EasySDL::Text infoAsc(EasySDL::POPPINS_REGULAR, 72);
Math::Pendulum pendulum(line.getAngle(),0,0,line.getLength(),0.0111);

void setup(){
    point.setup();

    pMass.setColor(EasySDL::RED_PINKY_NORMALIZED);
    pMass.setup();

    line.setup();
    infoAngle.setScale(0.2);
    infoAngle.setPos({400,460});
}

void draw(){
    line.draw(w);
    point.draw(w);
    pMass.draw(w);
    infoAngle.setMessage(line.getAngleDegStr());
    infoAngle.draw(w);
    line.setAngle(pendulum.calculateAngleNextIteration());
    pMass.setPos(line.getPosPoint2());
}

int main(){
    w->start(draw,setup);
}