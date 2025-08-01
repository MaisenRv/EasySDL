#include "../../include/EasySDL/Window.hpp"
#include <GL/glew.h>
#include "../../include/EasySDL/objects/particle/Particle.hpp"
#include "../../include/EasySDL/objects/line/Line.hpp"
#include "../../include/EasySDL/objects/line/ConstraintLine.hpp"
#include "../../include/EasySDL/objects/line/LineStrip.hpp"
#include "../../include/EasySDL/objects/text/Text.hpp"
#include "../../include/EasySDL/utils/pathList.hpp"
#include "../../include/EasySDL/utils/format.hpp"
#include "../../include/EasySDL/objects/square/Square.hpp"
#include "../../include/EasySDL/objects/chart/LineChart.hpp"

#include <cmath>
#include <cstdio>


EasySDL::Window *w = new EasySDL::Window(600, 600, "Ventana");
EasySDL::LineChart c({100,150},400,300,"Chart");
// EasySDL::LineStrip l (1);
// EasySDL::Text t(EasySDL::POPPINS_REGULAR, 72);

void setup()
{   
    c.addCurve("numero1",2);
    c.addCurve("numero2",2);
    c.addCurve("numero3",2);
    c.addCurve("numero4",2);

    c.setCurveColor("numero1",EasySDL::RED_PINKY_NORMALIZED);
    c.setCurveColor("numero2",EasySDL::MINT_GREEN_NORMALIZED);
    c.setCurveColor("numero3",EasySDL::GOLDEN_YELLOW_NORMALIZED);
    c.setCurveColor("numero4",EasySDL::LIGHT_CYAN_NORMALIZED);

    c.setup(); 
    // t.setScale(0.2);
    // t.setPos({100,50});
}


float ts = 0;
void draw()
{
    c.draw(w);
    c.addCoord({
        {"numero1",sin(M_PI * -c.getCurrentStep())*2.5 + 7.5 },
        {"numero2",sin(M_PI * c.getCurrentStep())*2.5 + 2.5 },
        {"numero3",sin(M_PI * -c.getCurrentStep()+ M_PI_2)*2.5 - 2.5},
        {"numero4",sin(M_PI * c.getCurrentStep() + M_PI_4)*2.5 - 7.5},

    });
//    l.draw(w);
    // t.setMessage(EasySDL::floatFormat(ts,2));
    // t.draw(w);
}

int main()
{
    w->start(draw, setup);
}