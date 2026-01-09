#pragma once
#include "../../interface/IDrawable.hpp"
#include "../../../Math/types/Vec2.hpp"
#include "../text/Text.hpp"
#include "../../utils/fonts.hpp"
#include "../shape/line/Line.hpp"
#include "../../utils/format.hpp"
#include "../../interface/IInitializable.hpp"
#include "../../interface/IWindow.hpp"
#include <memory>
#include <map>

namespace EasySDL
{
    class Chart : public EasySDL::IDrawable, public EasySDL::IInitializable{
        protected:
            // Chart info
            Vec2 _pos;
            float _width;
            float _height;

            // Chart title info
            EasySDL::Text _title;
            float _titleTextScale = 0.15;
            Vec2 _titlePos;
            std::string _titleStr;

            // Chart limits
            float _range[2] = {-1.0f, 1.0f};
            float _staticDomain[2] = {0.0f, 6.0f};
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

            // Show Chart
            bool _showTitle = true;
            bool _showGrid = true;
            bool _showBorder = true;


            // Limits functions
            float _calculateDomainLength() { return this->_staticDomain[1] - this->_staticDomain[0]; }
            float _calculateRangeLength() { return this->_range[1] - this->_range[0]; }


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
                if(!this->_showTitle) return;

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

            void _createBorder(){
                if(!this->_showBorder) return;

                this->_border[0] = std::make_unique<EasySDL::Line>(this->_topLeft.x    ,this->_topLeft.y    ,this->_topRight.x   ,this->_topRight.y   ,1);
                this->_border[1] = std::make_unique<EasySDL::Line>(this->_topRight.x   ,this->_topRight.y   ,this->_bottomRight.x,this->_bottomRight.y,1);
                this->_border[2] = std::make_unique<EasySDL::Line>(this->_bottomRight.x,this->_bottomRight.y,this->_bottomLeft.x ,this->_bottomLeft.y ,1);
                this->_border[3] = std::make_unique<EasySDL::Line>(this->_bottomLeft.x ,this->_bottomLeft.y ,this->_topLeft.x   ,this->_topLeft.y     ,1);
                for(size_t i = 0 ; i < 4 ;i++) this->_border[i]->setDeformable(false);
            }

            void _createLimitsInfo(){
                this->_limitsInfo.clear();
                this->_limitsInfo["x0"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
                this->_limitsInfo["x1"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
                this->_limitsInfo["y0"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
                this->_limitsInfo["y1"] = std::make_unique<EasySDL::Text>(EasySDL::POPPINS_REGULAR,16);
            }

            void _createChartGrid(){
                if(!this->_showGrid) return;

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

                for(auto& row: this->_rows) {
                    row->setDeformable(false);    
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

                for(auto& column: this->_columns) {
                    column->setDeformable(false);    
                }     

                for(auto& row: this->_rows) { row->setColor({1,1,1,0.2}); }
                for(auto& column: this->_columns) { column->setColor({1,1,1,0.2}); }
            }

            void _drawBorder(EasySDL::IWindow *w){
                if(!this->_showBorder) return;
                for(size_t i = 0 ; i < 4 ;i++) this->_border[i]->draw(w);
            }

            virtual void _drawLimitsInfo(EasySDL::IWindow *w){
                this->_limitsInfo["x0"]->setMessage(EasySDL::floatFormat(this->_staticDomain[0],2));
                this->_limitsInfo["x1"]->setMessage(EasySDL::floatFormat(this->_staticDomain[1],2));
                this->_limitsInfo["y0"]->setMessage(EasySDL::floatFormat(this->_range[0],2));
                this->_limitsInfo["y1"]->setMessage(EasySDL::floatFormat(this->_range[1],2));
                for(auto& limitInfo:this->_limitsInfo) limitInfo.second->draw(w);
            }

            void _drawGrid(EasySDL::IWindow *w){
                if(!this->_showGrid) return;
                for(auto& row: this->_rows) { row->draw(w); }
                for(auto& column: this->_columns) { column->draw(w); }
            }

            void _setupBorder(){
                if(!this->_showBorder) return;
                for (size_t i = 0; i < 4; i++) { this->_border[i]->setup(); }
            }

            void _onSetup() override {
                this->_updateBoundaries();
                this->_createBorder();
                this->_createLimitsInfo();
                this->_createChartGrid();
                this->_updateChartTitle();
                this->_updateLimitsInfo();

                if (this->_showBorder) this->_setupBorder();

                for(auto& row: this->_rows) { row->setup(); }
                for(auto& column: this->_columns) { column->setup(); }
            }

        public:
            Chart(Vec2 pos, float width, float height, std::string title):
            _pos(pos),
            _width(width),
            _height(height),
            _titleStr(title),
            _title(EasySDL::POPPINS_REGULAR, 64),
            _titlePos{ this->_pos.x + (this->_width / 2), this->_pos.y + this->_height + 15}{}

            void draw(EasySDL::IWindow *w) override {
                if(this->_showTitle)  this->_title.draw(w);
                
                this->_drawBorder(w);
                this->_drawGrid(w);
                this->_drawLimitsInfo(w);
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
            virtual void setDomain(float x0, float x1){
                this->_staticDomain[0] = x0;
                this->_staticDomain[1] = x1;
            }
            virtual void setRange(float y0, float y1){
                this->_range[0] = y0;
                this->_range[1] = y1;
                this->_createChartGrid();
            }

            // Show Chart
            void setShowTitle(bool show){ 
                this->_showTitle = show;
                this->_updateChartTitle();
            }
            void setShowGrid(bool show){
                this->_showGrid = show;
                this->_createChartGrid();
            }
            void setShowBorder(bool show){
                this->_showBorder = show;
                this->_createBorder();
                this->_setupBorder();
            }


    };
}