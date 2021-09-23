#include "velocity.h"


Velocity::Velocity(float Dx, float Dy)
{
    this->Dx = Dx;
    this->Dy = Dy;
}

Velocity::Velocity()
{
   this->Dx = 1;
   this->Dy = 1;
}
Velocity::~Velocity()
{

}

void Velocity::setDy(float Dy)
{
    this->Dy = Dy;
}

void Velocity::setDx(float Dx)
{
    this->Dx = Dx;
}

float Velocity::getDy()
{
    return Dy;
}

float Velocity::getDx()
{
    return Dx;
}
