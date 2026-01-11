// EasySDL objects 
#include "../../include/EasySDL/Window.hpp"
#include "../../include/EasySDL/objects/shape/particle/Particle.hpp"
#include "../../include/EasySDL/objects/text/Text.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/objects/chart/LineChart.hpp"
#include "../../include/Math/models/Pendulum.hpp"

// Includes
#include <cmath>

// Bindings
#include "wasm_bindings.hpp" 

extern "C" {
    void registerWindow(EasySDL::Window*);
}


int main(){
    // Change "WindowName" and "#canvasName"
    static EasySDL::Window *w = new EasySDL::Window(901, 450, "Pendulum","#pendulum");
   
    // Shapes
    EasySDL::Particle point(230, 250, 5, 50);
    EasySDL::Line line(230, 250, 200, 200, 2);
    EasySDL::Particle pMass(230, 50, 20, 50);
    EasySDL::Particle mouse(230, 50, 10, 50);

    Math::Pendulum pendulum(line.getAngle(),0,0,line.getLength(),0.0111);
    EasySDL::LineChart c({460,25},400,400,"Angle");

    // Call extern methods
    registerWindow(w);

    // Setop method
    auto setup = [&](){
        point.setDeformable(false);
        pMass.setDeformable(false);
        mouse.setDeformable(false);

        line.setLength(200);
        line.setLineAttachType(EasySDL::ATTACH_P1);

        point.setup();
        // pMass.setColor(EasySDL::RED_PINKY_NORMALIZED);
        pMass.setup();
        mouse.setup();
        line.setAngle(M_PI_2+M_PI_4);
        pendulum.setAngle(line.getAngle());
        line.setup();
        c.addCurve("angle",2);
        c.setCurveColor("angle",EasySDL::RED_PINKY_NORMALIZED);
        c.setStep(0.0111);
        c.setRange(-4.0f,1.0f);
        c.setDomain(0.0f,3.0f);
        c.setup();
    };
    // draw method
    auto draw = [&](){
        if(w->getMouseState().leftDown){
            pMass.setColor(EasySDL::RED_PINKY_NORMALIZED);
        }else if(w->getMouseState().rightDown){
            pMass.setColor(EasySDL::LIGHT_CYAN_NORMALIZED);
        }else{
            pMass.setColor(EasySDL::WHITE_NORMALIZED);
        }

        mouse.setPos({
            w->getMouseState().x,
            w->getHeight() - w->getMouseState().y
        });
        mouse.draw(w);
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
    };

    w->start(draw, setup);
}