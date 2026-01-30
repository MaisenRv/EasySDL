#pragma once
#include "../text/Text.hpp"
#include "../../../Math/types/Vec2.hpp"
#include "../../utils/fonts.hpp"
#include "../../utils/format.hpp"
#include "../../../Math/constans/Constans.hpp"
#include "../../interface/IWindow.hpp"
#include "Chart.hpp"
#include "../shape/line/LineStrip.hpp"
#include <string>
#include <vector>
#include <cmath>


namespace EasySDL
{
    class LineChart : public EasySDL::Chart 
    {
    private:

        // Curve info
        std::map<std::string, std::unique_ptr<EasySDL::LineStrip>> _curves;

        // Chart limits
        float _step = 0.02f;
        float _currentStep = 0.0f;
        bool _overflowDomain = false;

        void _shiftDomain(){ 
            this->_dinamicDomain[0] += this->_step;
            this->_dinamicDomain[1] += this->_step;
        }

        void _updateChartGridColumns(){
            if(!this->_showGrid) return;

            float shiftValue = this->_valueToPixelX(this->_step); 
            bool changeColumn = false;

            for(auto& column: this->_columns) { 
                column->shiftX(shiftValue);
                Math::Vec2 pos = column->getPosition();
                if (!changeColumn && pos.x <= this->_pos.x){
                    float x;
                    if(pos.x == this->_pos.x){
                        x = this->_topRight.x;
                    }else{
                        x = this->_topRight.x - (this->_pos.x - pos.x);
                    }
                    column->setPos({x,this->_topRight.y});
                    changeColumn = true;
                }
            }
        }
        
        void _drawLimitsInfo(EasySDL::IWindow *w) override {
            this->_limitsInfo["x0"]->setMessage(EasySDL::floatFormat(this->_dinamicDomain[0],2));
            this->_limitsInfo["x1"]->setMessage(EasySDL::floatFormat(this->_dinamicDomain[1],2));
            this->_limitsInfo["y0"]->setMessage(EasySDL::floatFormat(this->_range[0],2));
            this->_limitsInfo["y1"]->setMessage(EasySDL::floatFormat(this->_range[1],2));
            for(auto& limitInfo:this->_limitsInfo) limitInfo.second->draw(w);
        }
        void _onSetup() override{
            EasySDL::Chart::_onSetup();
            for(auto& curve: this->_curves){ curve.second->setup(); }
        }

    public:
        LineChart(Vec2 pos, float width, float height, std::string title): Chart(pos, width, height, title){}



        void draw(EasySDL::IWindow *w) override {
            EasySDL::Chart::draw(w);
            for (auto& curve : this->_curves) {
                curve.second->drawLineChart(
                    w, 
                    this->getDomainMin(),
                    this->getDomainMax(),
                    [&](float x, float y) -> Math::Vec2 {
                        return mapValueToPixelDinamicXY(x, y);
                    }
                );
            }
        }


        // chart.addCoords({
        //     {"temperatura",  23.4f},
        //     {"humedad",      60.2f},
        //     {"presion",    1013.8f}
        // });
        void addCoord(const std::map<std::string, float>& values,EasySDL::IWindow *w)
        {

             for (auto& [name, value] : values)
            {
                auto curve = this->_curves.find(name);
                if (curve == this->_curves.end()) continue;

                // X lógico (tiempo)
                float x = this->_currentStep;
                float y = value;
                

                curve->second->addPointLineChart({x, y});
                while (!curve->second->_points.empty() &&
                curve->second->_points.front().x < _dinamicDomain[0])
                {
                    curve->second->_points.erase(curve->second->_points.begin());
                }
            }

            // mover dominio si hace falta
            if (this->_currentStep > this->_dinamicDomain[1])
            {
                _shiftDomain();
                _updateChartGridColumns();
            }

            this->_currentStep += this->_step;
        }

        void addCurve(std::string name, GLfloat width){
            this->_curves[name] = std::make_unique<EasySDL::LineStrip>(width);
        }



    // -------- GETTERS SETTERS -------- 

        // CHART LIMITS
        void setStep(float step){  this->_step = step; }
        float getStep(){ return this->_step; }
        float getCurrentStep(){ return this->_currentStep; }
        void setDomain(float x0, float x1) override{
            EasySDL::Chart::setDomain(x0,x1);
            this->_dinamicDomain[0] = x0;
            this->_dinamicDomain[1] = x1;
        }
        void setRange(float y0, float y1) override{
            EasySDL::Chart::setRange(y0,y1);
            this->_dinamicRange[0] = y0;
            this->_dinamicRange[1] = y1;
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
        float getDomainMin(){
            return this->_dinamicDomain[0];
        }
        float getDomainMax(){
            return this->_dinamicDomain[1];
        }

    };
}