#include "ship.h"
#include "uiDraw.h"

// Put your ship methods here
Ship::Ship()
{
    velocity.setDx(0);
    velocity.setDy(0);
    point.setX(0);
    point.setY(0);
    rotation = 0;
    angle = 90;
    thrust = false;
    radius = 5;
}

void Ship::turnLeft()
{
    if(angle == 450)
    {
        angle = 90;
    }
    
    if(rotation == 360)
    {
        rotation = 0;
    }
    
    rotation += ROTATE_AMOUNT;
    angle += ROTATE_AMOUNT;
}

void Ship::turnRight()
{
    if(angle == 0)
    {
        angle = 360;
    }
    if(rotation == -360)
    {
        rotation = 0;
    }
    
    rotation -= ROTATE_AMOUNT;
    angle -= ROTATE_AMOUNT;
}

void Ship::applyThrust()
{
    thrust = true;
    velocity.setDx(velocity.getDx() + (- THRUST_AMOUNT * (-cos(M_PI / 180.0 * angle))));
    velocity.setDy(velocity.getDy() + (THRUST_AMOUNT * (sin(M_PI / 180.0 * angle))));
}

void Ship::draw()
{
    drawShip(point, rotation, thrust);
    thrust = false;
    //std::cout << point.getY() << std::endl;
}

int Ship::getAngle()
{
    return angle;
}

void Ship::setAngle(int angle)
{
    this->angle = angle;
    rotation = angle - 90;
}


