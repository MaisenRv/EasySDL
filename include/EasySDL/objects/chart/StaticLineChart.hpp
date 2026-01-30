#pragma once

#include "../shape/line/LineStrip.hpp"
#include "../shape/particle/Particle.hpp"
#include "../../interface/IWindow.hpp"
#include "Chart.hpp"
#include <functional>

namespace EasySDL
{
    class StaticLineChart: public EasySDL::Chart{
        private:
            // Curve info
            std::map<std::string, std::unique_ptr<EasySDL::LineStrip>> _curves;
            std::map<std::string, std::unique_ptr<EasySDL::Particle>> _points;

            // Chart limits
            float _step = 0.02f;

            void _onSetup() override {
                EasySDL::Chart::_onSetup();
                for(auto& curve: this->_curves){ curve.second->setup(); }
                for(auto& point: this->_points){ point.second->setup(); }
            }

        public:
            StaticLineChart(Math::Vec2 pos, float width, float height, std::string title): Chart(pos, width, height, title){
                this->setShowGrid(false);
            }

            void draw(EasySDL::IWindow *w) override{
                EasySDL::Chart::draw(w);
                for(auto& curve: this->_curves){ curve.second->draw(w); }
                for(auto& point: this->_points){ point.second->draw(w); }
            }

            void addCurve(std::string name, GLfloat width, const std::function<float(float)> f){
                this->_curves[name] = std::make_unique<EasySDL::LineStrip>(width);
                this->_points[name] = std::make_unique<EasySDL::Particle>();
                this->_points[name]->setDeformable(false);
                this->_updateBoundaries();
                bool setPointPos = true;
                for(float i = this->_staticDomain[0]; i < this->_staticDomain[1]; i+=this->_step){
                    Math::Vec2 position = this->mapValueToPixelXY(i,f(i));
                  
                    if(position.y > this->_topLeft.y || position.y < this->_bottomLeft.y) continue;
                    if(setPointPos){
                        this->_points[name]->setPos(position);
                        setPointPos = false;
                    }
                    this->_curves[name]->addPoint(position);
                }
                this->_curves[name]->setDeformable(false);
            }

        // -------- GETTERS SETTERS -------- 

            // CURVES
            void setCurveColor(std::string name, const float (&color)[4] ){
                auto curve = this->_curves.find(name);
                auto point = this->_points.find(name);
                if (curve == this->_curves.end()) return;
                curve->second->setColor(color);
                point->second->setColor(color);
            }

            void setPointPosition(const std::string name, const float x,const float y){
                auto point = this->_points.find(name);
                if (point == this->_points.end()) return;
                point->second->setPos(
                    this->mapValueToPixelXY(x,y)
                );
            }

    };
}