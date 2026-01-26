#pragma once
#include "../constans/Constans.hpp"
#include "../methods/Euler.hpp"
#include <cmath>
#include <iostream>

namespace Math
{
    class Pendulum
    {
    private:
    public:
        float angle;
        float vel;
        float length;
        float t;
        float step;
        const float ROTATION = -M_PI_2;
        Pendulum(float angle0, float vel0, float t0, float length, float step):
        angle(angle0),vel(vel0),t(t0),length(length/400),step(step){}
        
        float calculateAngleNextIteration()
        {
            Math::EulerMethod2Order(
                this->vel,
                this->angle,
                this->step,
                this->t,
                this->methodLagrange()
            );
            return this->angle + this->ROTATION;
        }

        float methodLagrange()
        {
            return (-Math::G.y * sin(this->angle)) / this->length;
        }
        void setAngle(float angle){
            this->angle = angle;
        }

        void setLength(float newLength){
            this->length = newLength/400;
            this->restart();
        }
        void restart(){
            this->t = 0;
            this->vel = 0;
           
        }
    };
}
