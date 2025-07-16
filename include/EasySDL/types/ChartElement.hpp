#pragma once
#include "../objects/line/Line.hpp"
#include "../objects/text/Text.hpp"

namespace EasySDL
{
    struct ChartElement
    {
        EasySDL::Line *line;
        EasySDL::Text *value;

        ChartElement(EasySDL::Line *line,EasySDL::Text *value):line(line),value(value){}

        ~ChartElement(){
            delete line,
            delete value;
        }
    };
    
}