#pragma once
#include "../line/Line.hpp"
#include "../line/LineStrip.hpp"
#include "../text/Text.hpp"
#include "../../types/Vec2.hpp"
#include "../../types/ChartElement.hpp"
#include "../../Window.hpp"
#include "../../utils/pathList.hpp"
#include "../../utils/format.hpp"
#include <string>
#include <vector>
#include <memory>


namespace EasySDL
{
    class LineChart
    {
    private:
        // Chart info
        Vec2 _pos;
        float _width;
        float _height;
        EasySDL::Text _title;
        float _titleTextScale = 0.15;
        Vec2 _titlePos;

        // ChartElements info
        float _range[2] = {-1, 1};
        float _domain[2] = {0, 1};
        float _step = 0.5;
        int _nRows = 2;
        int _nColums = 2;
        float _deltaY = 0;
        float _deltaX = 0;
        float _lineColor[4] = {1, 1, 1, 0.5};
        std::vector<std::unique_ptr<ChartElement>> _rows;
        std::vector<std::unique_ptr<ChartElement>> _colums;
        float _domainOffset = 0.0f;
            // contans
        const float COORD_TOP_Y = this->_pos.y + this->_height;
        const float COORD_RIGHT_X = this->_pos.x + this->_width;

        // curve info
        int _totalSteps = 600;
        float _deltaTotalSteps = this->_width / this->_totalSteps;
        float _reescaleDeltaX = this->_calculateDomainLength() / this->_totalSteps;
        EasySDL::LineStrip _curve;
        

        float _calculateDomainLength() { return this->_domain[1] - this->_domain[0]; }
        float _calculateRangeLength() { return this->_range[1] - this->_range[0]; }
        float _rescaleValueX(float value){ return (value - this->_domain[0]) / (this->_domain[1] - this->_domain[0]); }
        float _rescaleValueY(float value){ return (value - this->_range[0]) / (this->_range[1] - this->_range[0]); }
        
        void _updateReescaleDeltaX(){ this->_reescaleDeltaX = this->_calculateDomainLength() / this->_totalSteps; }

        void _createColums()
        {
            this->_nColums = (int)((this->_domain[1] - this->_domain[0]) / this->_step);
            this->_deltaX = this->_width / this->_nColums;

            for (size_t i = 0; i <= this->_nColums; i++)
            {
                float x = this->_pos.x + (i * this->_deltaX);
                std::unique_ptr<EasySDL::Line> line = std::make_unique<EasySDL::Line>(x, this->_pos.y, x, this->COORD_TOP_Y, 1);
                std::unique_ptr<EasySDL::Text> text = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR, 32);
                line->setColor(this->_lineColor);
                line->setup();
                text->setScale(0.2);
                text->setPos({this->_pos.x + (i * this->_deltaX), this->_pos.y - 10});
                text->setMessage(EasySDL::floatFormat(this->_domain[0] + (i * this->_step),2));
                std::unique_ptr<ChartElement> row = std::make_unique<ChartElement>(std::move(line), std::move(text));
                this->_colums.push_back(std::move(row));
            }
        }

        void _updateColums(){
            for (size_t i = 0; i <= this->_nColums; i++)
            {
                this->_colums[i]->line->shiftX(this->_deltaTotalSteps);
                this->_colums[i]->value->shiftX(this->_deltaTotalSteps);
                if( this->_colums[i]->line->getVertexList()[0] < this->_pos.x || 
                    this->_colums[i]->line->getVertexList()[0] > this->COORD_RIGHT_X
                ){
                    this->_colums[i]->visible = false;
                }else{
                    this->_colums[i]->visible = true;
                }
            }
        }

        void _createRows()
        {
            this->_nRows = (int)(this->_calculateRangeLength() / this->_step);
            float x0 = this->_pos.x;
            float x1 = this->_pos.x + this->_width;

            this->_deltaY = this->_height / this->_nRows;
            for (size_t i = 0; i <= this->_nRows; i++)
            {
                float y = this->_pos.y + (i * this->_deltaY);
                std::unique_ptr<EasySDL::Line> line = std::make_unique<EasySDL::Line>(x0, y, x1, y, 1);
                std::unique_ptr<EasySDL::Text> text = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR, 32);
                line->setColor(this->_lineColor);
                line->setup();
                text->setScale(0.2);
                text->setPos({this->_pos.x + this->_width + 20, this->_pos.y + (i * this->_deltaY)});
                text->setMessage(EasySDL::floatFormat((this->_range[0] + (i * this->_step)),2));
                std::unique_ptr<ChartElement> row = std::make_unique<ChartElement>(std::move(line), std::move(text));

                this->_rows.push_back(std::move(row));
            }
        }



    public:
        std::string titleStr;

        LineChart(Vec2 pos, float width, float height, std::string title) : _pos(pos),
                                                                            _width(width),
                                                                            _height(height),
                                                                            titleStr(title),
                                                                            _title(EasySDL::POPPINS_REGULAR, 64),
                                                                            _titlePos{0, 0},
                                                                            _curve(2) {}

        void setup()
        {
            this->_createRows();
            this->_createColums();
            this->_curve.setColor(EasySDL::RED_PINKY_NORMALIZED);
            this->_curve.setup();
            this->_title.setScale(this->_titleTextScale);

            this->_titlePos = { this->_pos.x + (this->_width / 2), this->_pos.y + this->_height + 10};
            this->_title.setPos({this->_titlePos.x, this->_titlePos.y});
            this->_title.setMessage(this->titleStr);
        }

        void draw(EasySDL::Window *w)
        {
            this->_title.draw(w);

            for (size_t i = 0; i <= this->_nRows; i++)
            {
                this->_rows[i]->line->draw(w);
                this->_rows[i]->value->draw(w);
            }
            for (size_t i = 0; i <= this->_nColums; i++)
            {
                if (!this->_colums[i]->visible) continue;
                
                this->_colums[i]->line->draw(w);
                this->_colums[i]->value->draw(w);
            }
            this->_curve.draw(w);
            if (this->_curve.getVertexSize() >= this->_totalSteps){
                this->_updateColums();
            }
        }

        void addCoord(float y)
        {
            float newY = this->_pos.y + this->_rescaleValueY(y) * this->_height;
            float newX = this->_pos.x + (this->_curve.getVertexSize() * this->_deltaTotalSteps);

            if (this->_curve.getVertexSize() >= this->_totalSteps)
            {
                this->_curve.removeFirstPoint();
                this->_curve.shiftX(this->_deltaTotalSteps);
                this->_domainOffset += this->_reescaleDeltaX;
            }

            this->_curve.addPoint({ newX, newY });
        }
    };
}