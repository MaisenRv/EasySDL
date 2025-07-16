#include "../../include/EasySDL/Window.hpp"
#include <GL/glew.h>
#include "../../include/EasySDL/objects/particle/Particle.hpp"
#include "../../include/EasySDL/objects/line/Line.hpp"
#include "../../include/EasySDL/objects/line/ConstraintLine.hpp"
#include "../../include/EasySDL/objects/line/LineStrip.hpp"
#include "../../include/EasySDL/objects/text/Text.hpp"
#include "../../include/EasySDL/utils/pathList.hpp"
#include "../../include/EasySDL/objects/square/Square.hpp"
#include "../../include/EasySDL/objects/chart/LineChart.hpp"

#include <cstdio>


EasySDL::Window *w = new EasySDL::Window(600, 600, "Ventana");
EasySDL::LineChart c({100,100},400,400,"Chart");
// EasySDL::LineStrip l (1);

void setup()
{   
    c.setup();
    // l.setup();   
    // l.addPoint({100,100});
    // l.addPoint({200,200});
    // l.addPoint({0,600});
}


void draw()
{
    c.draw(w);
//    l.draw(w);
}

int main()
{
    w->start(draw, setup);
}