#include "flyingObject.h"


// Put your FlyingObject method bodies here
FlyingObject::FlyingObject() :  alive(true)
{
    
}

FlyingObject::~FlyingObject()
{

    
}

void FlyingObject::setPoint(Point p)
{
    this->point = p;

}

void FlyingObject::setVelocity(Velocity v)
{
    this->velocity = v;
}

void FlyingObject::setTopLeft(Point tl)
{
    topLeft = tl;
}

void FlyingObject::setBottomRight(Point br)
{
    bottomRight = br;
}


Point FlyingObject::getPoint()
{
    return point;
}

Velocity FlyingObject::getVelocity()
{
    return velocity;
}

int FlyingObject::getRadius()
{
    return radius;
}

void FlyingObject::advance()
{
    point.setX(point.getX() + velocity.getDx());
    if(point.getX() > bottomRight.getX() + radius)
    {
        point.setX(topLeft.getX() - radius);
    }
    else if (point.getX() < topLeft.getX() - radius)
    {
        point.setX(bottomRight.getX() + radius);
    }
    
    point.setY(point.getY() + velocity.getDy());
    if(point.getY() < bottomRight.getY() - radius)
    {
        point.setY(topLeft.getY() + radius);
    }
    else if (point.getY() > this->topLeft.getY() + radius)
    {
        point.setY(bottomRight.getY() - radius);
    }
}

void FlyingObject::kill()
{
    alive = false;
}

void FlyingObject::draw()
{
    
}

void FlyingObject::setAlive(bool alive)
{
    this->alive = alive;
}

bool FlyingObject::isAlive()
{
   return alive;
}

void FlyingObject::setDy(float Dy)
{
    velocity.setDy(Dy);
}

void FlyingObject::setDx(float Dx)
{
    velocity.setDx(Dx);
}

float FlyingObject::getDy()
{
    return velocity.getDy();
}

float FlyingObject::getDx()
{
    return velocity.getDx();
}
