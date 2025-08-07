
#include "../../include/EasySDL/Window.hpp"
#include "../../include/EasySDL/objects/shape/particle/Particle.hpp"
#include "../../include/EasySDL/objects/shape/line/ConstraintLine.hpp"
#include "../../include/EasySDL/objects/text/Text.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/objects/chart/LineChart.hpp"

#include "../../include/Math/models/Pendulum.hpp"
#include <cmath>


EasySDL::Window *w = new EasySDL::Window(900, 450, "Pendulum");
EasySDL::Particle point(230, 250, 5, 50);
EasySDL::ContraintLine line(230, 250, 200, 200, 2, 200);
EasySDL::Particle pMass(230, 50, 20, 50);

EasySDL::Text fps(EasySDL::POPPINS_REGULAR,16);

Math::Pendulum pendulum(line.getAngle(),0,0,line.getLength(),0.0111);

// char
EasySDL::LineChart c({460,25},400,400,"Angle");

void setup(){
    point.setup();

    pMass.setColor(EasySDL::RED_PINKY_NORMALIZED);
    pMass.setup();
    line.setAngle(M_PI_2+M_PI_4);
    pendulum.setAngle(line.getAngle());
    line.setup();
    
    c.addCurve("angle",2);
    c.setCurveColor("angle",EasySDL::RED_PINKY_NORMALIZED);
    c.setStep(0.0111);
    c.setRange(-4.0f,1.0f);
    c.setDomain(0.0f,3.0f);
    // c.setShowTitle(false);
    // c.setShowGrid(false);
    // c.setShowBorder(false);
    c.setup();
    

    fps.setPos({25,20});
    fps.setScale(0.5);
}

void draw(){
    line.draw(w);
    point.draw(w);
    pMass.draw(w);
    float angle = pendulum.calculateAngleNextIteration();
    line.setAngle(angle);
    pMass.setPos(line.getPosPoint2());
    c.addCoord({
        {"angle", angle}
    },w);
    c.draw(w);
    fps.setMessage(EasySDL::floatFormat(w->getFPS(),1));
    fps.draw(w);
}

int main(){
    w->start(draw,setup);
}