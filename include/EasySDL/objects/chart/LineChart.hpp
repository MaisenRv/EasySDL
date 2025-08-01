#pragma once
#include "../line/Line.hpp"
#include "../line/LineStrip.hpp"
#include "../text/Text.hpp"
#include "../../types/Vec2.hpp"
#include "../../Window.hpp"
#include "../../utils/pathList.hpp"
#include "../../utils/format.hpp"
#include "../../../Math/constans/Constans.hpp"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <cmath>


namespace EasySDL
{
    class LineChart
    {
    private:
        // Chart info
        Vec2 _pos;
        float _width;
        float _height;

        // Chart title info
        EasySDL::Text _title;
        float _titleTextScale = 0.15;
        Vec2 _titlePos;
        std::string _titleStr;

        // Curve info
        std::map<std::string, std::unique_ptr<EasySDL::LineStrip>> _curves;

        // Chart limits
        float _range[2] = {-1.0f, 1.0f};
        float _staticDomain[2] = {0.0f, 6.0f};
        float _dinamicDomain[2] = {0.0f, 6.0f};
        float _step = 0.02f;
        float _currentStep = 0.0f;
        bool _overflowDomain = false;
        std::map<std::string, std::unique_ptr<EasySDL::Text>> _limitsInfo;
        float _textScale = 0.4f;

        // Chart boundaries
        Vec2 _topLeft;
        Vec2 _topRight;
        Vec2 _bottomRight;
        Vec2 _bottomLeft;
        std::unique_ptr<EasySDL::Line> _border[4];

        // Chart grid
        std::vector<std::unique_ptr<EasySDL::Line>> _rows;
        std::vector<std::unique_ptr<EasySDL::Line>> _columns;

        // Limits functions
        float _calculateDomainLength() { return this->_staticDomain[1] - this->_staticDomain[0]; }
        float _calculateRangeLength() { return this->_range[1] - this->_range[0]; }
        void _shiftDomain(){ 
            this->_dinamicDomain[0] += this->_step;
            this->_dinamicDomain[1] += this->_step;
        }

        // Outside the chart
        float _valueToPixelY(float value){
            return ((value - this->_range[0]) / this->_calculateRangeLength()) * this->_height;
        }
        float _valueToPixelX(float value){
            return ((value - this->_staticDomain[0]) / this->_calculateDomainLength()) * this->_width;
        }

        // Inside the chart
        float _mapValueToPixelY(float value){ 
            return this->_valueToPixelY(value) + this->_pos.y;
        }
        float _mapValueToPixelX(float value){
            return this->_valueToPixelX(value) + this->_pos.x;
        }

        Vec2 _mapValueToPixelXY(float valueX, float valueY){
            return  {this->_mapValueToPixelX(valueX), this->_mapValueToPixelY(valueY)};
        }

        float _niceNum(float x) {
            float expv = std::floor(std::log10(x));    
            float f    = x / std::pow(10, expv);       
            float nf;
            if (f < 1.5f)      nf = 1.0f;
            else if (f < 3.0f) nf = 2.0f;
            else if (f < 7.0f) nf = 5.0f;
            else               nf = 10.0f;
            return nf * std::pow(10, expv);
        }

        void _updateChartTitle(){
            this->_title.setPos({this->_titlePos.x, this->_titlePos.y});
            this->_title.setScale(this->_titleTextScale);
            this->_title.setMessage(this->_titleStr);
        }

        void _updateBoundaries(){
            this->_topLeft     = {this->_pos.x                ,this->_pos.y + this->_height};
            this->_topRight    = {this->_pos.x + this->_width ,this->_pos.y + this->_height};
            this->_bottomRight = {this->_pos.x + this->_width ,this->_pos.y};
            this->_bottomLeft  = {this->_pos.x                ,this->_pos.y};
        }

        void _updateLimitsInfo(){
            for (auto& limitInfo: this->_limitsInfo){ limitInfo.second->setScale(this->_textScale); }
            
            this->_limitsInfo["x0"]->setPos({this->_bottomLeft.x      ,this->_bottomLeft.y - 10 });
            this->_limitsInfo["x1"]->setPos({this->_bottomRight.x     ,this->_bottomRight.y - 10});
            this->_limitsInfo["y0"]->setPos({this->_bottomRight.x + 20,this->_bottomRight.y     });
            this->_limitsInfo["y1"]->setPos({this->_topRight.x + 20   ,this->_topRight.y        });
        }

        void _updateChartGridColumns(){
            bool changeColumn = false;
            for(auto& column: this->_columns) { 
                float shiftValue = this->_valueToPixelX(this->_step); 
                column->shiftX(shiftValue);
                if (!changeColumn && column->getVertexList()[0] <= this->_pos.x){
                    float x;
                    if(column->getVertexList()[0] == this->_pos.x){
                        x = this->_topRight.x;
                    }else{
                        x = this->_topRight.x - (this->_pos.x - column->getVertexList()[0]);
                    }

                    column->setPositions(
                        x, this->_topRight.y,
                        x, this->_bottomRight.y
                    );
                    changeColumn = true;
                }
            }
        }


        void _createBorder(){
            this->_border[0] = std::make_unique<EasySDL::Line>(this->_topLeft.x    ,this->_topLeft.y    ,this->_topRight.x   ,this->_topRight.y   ,1);
            this->_border[1] = std::make_unique<EasySDL::Line>(this->_topRight.x   ,this->_topRight.y   ,this->_bottomRight.x,this->_bottomRight.y,1);
            this->_border[2] = std::make_unique<EasySDL::Line>(this->_bottomRight.x,this->_bottomRight.y,this->_bottomLeft.x ,this->_bottomLeft.y ,1);
            this->_border[3] = std::make_unique<EasySDL::Line>(this->_bottomLeft.x ,this->_bottomLeft.y ,this->_topLeft.x   ,this->_topLeft.y     ,1);   
        }

        void _createLimitsInfo(){
            this->_limitsInfo.clear();
            this->_limitsInfo["x0"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
            this->_limitsInfo["x1"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
            this->_limitsInfo["y0"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
            this->_limitsInfo["y1"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
        }

        void _createChartGrid(){
            this->_rows.clear();
            this->_columns.clear();
            int targetRows;
            if (this->_height <= 200)       targetRows = 5;
            else if (this->_height <= 500)  targetRows = 8;
            else                            targetRows = 10;
            float range = this->_calculateRangeLength();
            float stepY = this->_niceNum(range / targetRows);
            for(float i = this->_range[0]; i < this->_range[1]; i+= stepY){
                float y = this->_mapValueToPixelY(i);
                this->_rows.push_back(std::make_unique<EasySDL::Line>(
                    this->_bottomLeft.x, 
                    y,
                    this->_bottomRight.x,
                    y, 
                    1
                ));
            }   

            int targetColumns;
            if (this->_width <= 200)       targetColumns = 5;
            else if (this->_width <= 500)  targetColumns = 8;
            else                           targetColumns = 10;
            float domain = this->_calculateDomainLength();
            float stepX = this->_niceNum(domain / targetColumns);
            for(float i = this->_staticDomain[0]; i < this->_staticDomain[1]; i+=stepX){
                float x = this->_mapValueToPixelX(i);
                this->_columns.push_back(std::make_unique<EasySDL::Line>(
                    x, 
                    this->_topLeft.y,
                    x,
                    this->_bottomLeft.y, 
                    1
                ));
            } 

            for(auto& row: this->_rows) { row->setColor({1,1,1,0.2}); }
            for(auto& column: this->_columns) { column->setColor({1,1,1,0.2}); }
        }


        void _drawBorder(EasySDL::Window *w){
            for(size_t i = 0 ; i < 4 ;i++) this->_border[i]->draw(w);
        }
        void _drawLimitsInfo(EasySDL::Window *w){
            this->_limitsInfo["x0"]->setMessage(EasySDL::floatFormat(this->_dinamicDomain[0],2));
            this->_limitsInfo["x1"]->setMessage(EasySDL::floatFormat(this->_dinamicDomain[1],2));
            this->_limitsInfo["y0"]->setMessage(EasySDL::floatFormat(this->_range[0],2));
            this->_limitsInfo["y1"]->setMessage(EasySDL::floatFormat(this->_range[1],2));
            for(auto& limitInfo:this->_limitsInfo) limitInfo.second->draw(w);
        }
        void _drawGrid(EasySDL::Window *w){
            for(auto& row: this->_rows) { row->draw(w); }
            for(auto& column: this->_columns) { column->draw(w); }
        }

    public:


        LineChart(Vec2 pos, float width, float height, std::string title) : 
        _pos(pos),
        _width(width),
        _height(height),
        _titleStr(title),
        _title(EasySDL::POPPINS_REGULAR, 64),
        _titlePos{0, 0} {

            this->_titlePos = { this->_pos.x + (this->_width / 2), this->_pos.y + this->_height + 10};
            this->_updateBoundaries();
            this->_createBorder();
            this->_createLimitsInfo();
            this->_createChartGrid();
        }

        void setup()
        {
            this->_updateChartTitle();
            this->_updateLimitsInfo();
            for(auto& curve: this->_curves){ curve.second->setup(); }
            for (size_t i = 0; i < 4; i++) { this->_border[i]->setup(); }
            for(auto& row: this->_rows) { row->setup(); }
            for(auto& column: this->_columns) { column->setup(); }
        }

        void draw(EasySDL::Window *w)
        {
            this->_title.draw(w);
            this->_drawBorder(w);
            this->_drawGrid(w);
            this->_drawLimitsInfo(w);
            for(auto& curve: this->_curves){ curve.second->draw(w); }
        }


        // chart.addCoords({
        //     {"temperatura",  23.4f},
        //     {"humedad",      60.2f},
        //     {"presion",    1013.8f}
        // });
        void addCoord(const std::map<std::string, float>& values,EasySDL::Window *w)
        {
            for(auto& [name,value]:values){
                auto curve = this->_curves.find(name);
                if(curve == this->_curves.end()) continue;
                
                float newX;
                if(this->_overflowDomain){
                    curve->second->removeFirstPoint();
                    curve->second->shiftX(this->_valueToPixelX(this->_step),w);
                    newX = this->_topRight.x;
                }

                if(!this->_overflowDomain){
                    if(this->_currentStep >= this->_staticDomain[1]){
                        newX = this->_topRight.x;
                        this->_overflowDomain = true;
                    }else{
                        newX = this->_mapValueToPixelX(this->_currentStep);
                    }
                }     

                float newY = this->_mapValueToPixelY(value);
                curve->second->addPoint({newX, newY});
            }
            if(this->_overflowDomain) {
                this->_shiftDomain();
                this->_updateChartGridColumns();
            };
            this->_currentStep += this->_step;
        }

        void addCurve(std::string name, GLfloat width){
            this->_curves[name] = std::make_unique<EasySDL::LineStrip>(width);
        }



    // -------- GETTERS SETTERS -------- 

        // CHART
        Vec2 getPos(){ return this->_pos; }
        void setPos(float x, float y){ this->_pos = {x,y}; }
        float getWidth(){ return this->_width; }
        void setWidth(float width){ this->_width = width; }
        float getHeight(){ return this->_height; }
        void setHeight(float height){ this->_height = height; }

        // CHART TITLE
        float getTitleTextScale(){ return this->_titleTextScale; }
        Vec2 getTitlePos(){ return this->_titlePos; }
        void setTitleTextScale(float scale){ 
            this->_titleTextScale =  scale; 
            this->_updateChartTitle();
        }
        void setTitleStr(std::string title ){ 
            this->_titleStr = title; 
            this->_updateChartTitle();
        }
        void setTitlePos(float x, float y) { 
            this->_titlePos = {x,y}; 
            this->_updateChartTitle();
        }

        // CHART LIMITS
        void setStep(float step){ 
            this->_step = step;
        }
        float getStep(){ return this->_step; }
        float getCurrentStep(){ return this->_currentStep; }
        void setDomain(float x0, float x1){
            this->_staticDomain[0] = x0;
            this->_staticDomain[1] = x1;
            this->_dinamicDomain[0] = x0;
            this->_dinamicDomain[1] = x1;
        }
        void setRange(float y0, float y1){
            this->_range[0] = y0;
            this->_range[1] = y1;
            this->_createChartGrid();
        }

        // CURVES
        std::unique_ptr<EasySDL::LineStrip>& getCurve(std::string name){
            return this->_curves.find(name)->second; 
        }
        void setCurveColor(std::string name, const float (&color)[4] ){
            auto curve = this->_curves.find(name);
            if (curve == this->_curves.end()) return;
            curve->second->setColor(color);
        }

    };
}