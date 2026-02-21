// EasySDL objects 
#include "../../include/EasySDL/Window.hpp"
#include "../../include/EasySDL/objects/shape/particle/Particle.hpp"
#include "../../include/EasySDL/objects/text/Text.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/objects/chart/LineChart.hpp"
#include "../../include/Math/models/Pendulum.hpp"
#include "../../include/EasySDL/objects/button/Button.hpp"
#include "../../include/EasySDL/Scene.hpp"
// Includes
#include <cmath>

// Bindings
#include "wasm_bindings.hpp" 

extern "C" {
    void registerWindow(EasySDL::Window*);
}

int main(){
    // Change "WindowName" and "#canvasName"
    static EasySDL::Window *w = new EasySDL::Window(900, 450, "Pendulum","#pendulum");
    EasySDL::Scene sceneObjects;
    // Shapes
    EasySDL::Particle point(230, 250, 5, 50);
    EasySDL::Line line(230, 250, 200, 200, 4);
    EasySDL::Particle pMass(230, 50, 20, 50);
    EasySDL::Particle mouse(230, 50, 5, 50);
    EasySDL::Button b({230,410},80,20,5,8,"Stop");
    Math::Pendulum pendulum(line.getAngle(),0,0,line.getLength(),0.0111);
    EasySDL::LineChart c({460,25},400,400,"Angle");
    EasySDL::Text textAngle(EasySDL::POPPINS_REGULAR,16);

    // Call extern methods
    registerWindow(w);

    bool animationState = true;
    float angle = 0;
    float length = 200.0f;
    float lengthChange = 10.0f;
    // Setop method
    auto setup = [&](){
        b.setIsActivateCollitions(true);
        b.setActivateHover(true);

        pMass.setColor(EasySDL::RED_PINKY_NORMALIZED);
        pMass.setIsActivateCollitions(true);
        b.setColor(EasySDL::RED_PINKY_NORMALIZED);
        
        line.setDeformable(true);
        line.setLength(length);
        line.setLineAttachType(EasySDL::ATTACH_P1);
        line.setColor(EasySDL::GOLDEN_YELLOW_NORMALIZED);
        line.setAngle(M_PI_2+M_PI_4);
        
        line.setup();
        pMass.setup();
        mouse.setup();
        point.setup();
        b.setup();
       
        
        pendulum.setAngle(line.getAngle());
        
        c.addCurve("angle",2);
        c.setCurveColor("angle",EasySDL::MINT_GREEN_NORMALIZED);
        c.setStep(0.0111);
        c.setRange(-4.5f,1.5f);
        c.setDomain(0.0f,3.0f);
        c.setup();

        textAngle.setPos({c.getPos().x + 30,c.getPos().y + c.getHeight() - 18});
        textAngle.setTextColor(EasySDL::MINT_GREEN_SDL);
        textAngle.setScale(0.6);
        // textAngle.setUpdatebleTexture(true);

        sceneObjects.addObject(textAngle);
        sceneObjects.addObject(line);
        sceneObjects.addObject(point);
        sceneObjects.addObject(pMass);
        sceneObjects.addObject(c);
        sceneObjects.addObject(b);
        sceneObjects.addObject(mouse);

    };
    // draw method
    auto draw = [&](){
        Math::Vec2 mousePosition = {w->getMouseState().x,w->getHeight() - w->getMouseState().y};
        if(b.IsColliding(mousePosition)){
            if(animationState){
                b.executeClickEvent(w->getMouseState().leftDown,
                [&]{
                    b.setColor(EasySDL::MINT_GREEN_NORMALIZED);
                    animationState = !animationState; 
                    b.setText("Play");
                });
            }else if(!animationState){
                b.executeClickEvent(w->getMouseState().leftDown,
                [&]{
                    b.setColor(EasySDL::RED_PINKY_NORMALIZED);
                    animationState = !animationState; 
                    b.setText("Stop");
                });
            }
        }

        


        b.hoverScaleAnimation(0.05,1.2);
        mouse.setPos({
            w->getMouseState().x,
            w->getHeight() - w->getMouseState().y
        });

        
        
        if(animationState){
            angle = pendulum.calculateAngleNextIteration();
            line.setAngle(angle);
            pMass.setPos(line.getPosPoint2());
            c.addCoord({
                {"angle", angle}
            },w);
        }
            
        textAngle.setMessage(EasySDL::floatFormat(angle,2));

        sceneObjects.drawScene(w);
    };

    w->start(draw, setup);
    delete w;
}