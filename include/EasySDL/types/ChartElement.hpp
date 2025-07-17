#pragma once
#include "../objects/line/Line.hpp"
#include "../objects/text/Text.hpp"
#include <memory>
namespace EasySDL
{
    struct ChartElement
    {
        std::unique_ptr<EasySDL::Line> line;
        std::unique_ptr<EasySDL::Text> value;
        bool visible = true;

        ChartElement(std::unique_ptr<EasySDL::Line> line, std::unique_ptr<EasySDL::Text> value) : line(std::move(line)), value(std::move(value)) {}
    };

}