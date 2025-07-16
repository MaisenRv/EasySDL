#pragma once
#include "../line/Line.hpp"
#include "../line/LineStrip.hpp"
#include "../text/Text.hpp"
#include "../../types/Vec2.hpp"
#include "../../types/ChartElement.hpp"
#include "../../Window.hpp"
#include "../../utils/pathList.hpp"
#include <string>
#include <vector>

namespace EasySDL
{
    class LineChart
    {
    private:
        Vec2 _pos;
        int _width;
        int _height;

        EasySDL::Line _bottomLine;
        EasySDL::Text _title;

        float _titleTextScale = 0.15;
        Vec2 _titlePos;


        float _range[2] = {0,1}; 
        int _step = 0.5; 

        std::vector<ChartElement> rows;
        std::vector<ChartElement> colums;


        void _staticDraw(EasySDL::Window *w){
            this->_bottomLine.draw(w);
            this->_title.draw(w,this->titleStr,this->_titlePos.x,this->_titlePos.y,this->_titleTextScale);
            if(this->_titlePos.x == 0){
                this->_titlePos = {
                    this->_pos.x + (this->_width / 2), 
                    this->_pos.y + this->_height + 10
                };
            }
        }

    public:
        std::string titleStr;
        
        LineChart(Vec2 pos, int width, int height,std::string title) : 
        _pos(pos), 
        _width(width), 
        _height(height), 
        titleStr(title),
        _title(EasySDL::POPPINS_REGULAR,64), 
        _bottomLine(0,0,0,0,1),
        _titlePos{0,0}
        {
            this->_bottomLine.setPositions(this->_pos.x,this->_pos.y,this->_pos.x + this->_width,this->_pos.y);
            
        }

        void setup(){
            this->_bottomLine.setup();
        }

        void draw(EasySDL::Window *w){
            this->_staticDraw(w);
        }

    };
}