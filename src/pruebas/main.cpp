#include "../../include/EasySDL/Window.hpp"
#include "../../include/EasySDL/objects/shape/line/Line.hpp"
#include "wasm_bindings.hpp"

extern "C"{
     void registerLine(EasySDL::Line*);
}

int main()
{
    EasySDL::Window *w = new EasySDL::Window(600, 600, "Ventana");
    static EasySDL::Line l(0,300,600,300,2);
    
    registerLine(&l);
    auto setup = [&](){   
        l.setup();
    };

    auto draw = [&](){
        l.draw(w);
    };

    w->start(draw, setup);
}