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

        const float ROTATION = -1.5708;
        Pendulum(float angle0, float vel0, float t0, float length, float step):
        angle(angle0),vel(vel0),t(t0),length(length/400),step(step) {}
        
        float calculateAngleNextIteration()
        {
            this->vel = Math::EulerMethod(
                this->vel,
                this->step,
                this->t,
                this->methodLagrange());
            this->angle = Math::EulerMethod(
                this->angle,
                this->step,
                this->t,
                this->vel);
            return this->angle + this->ROTATION;
        }

        float methodLagrange()
        {
            return (-Math::G.y * sin(this->angle)) / this->length;
        }
        void setAngle(float angle){
            this->angle = angle;
        }
    };
}
