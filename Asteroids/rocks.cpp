#include "rocks.h"
#include "uiDraw.h"


// Put your Rock methods here

Rock::Rock()
{
   angle = random(0, 361);
}

void Rock::setConstRotation(int rotation)
{
    this->constRotation = rotation;
}

BigRock::BigRock(Point topLeft, Point bottomRight)
{
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    int rightOrLeft = random(0, 2);
    int yLocation = random(bottomRight.getY() + 20, topLeft.getY() - 20);
    if(rightOrLeft == 0)
    {
        point.setX(topLeft.getX() + 20);
        point.setY(yLocation);
        velocity.setDx(BIG_ROCK_SPEED * (-cos(M_PI / 180.0 * angle)));
        velocity.setDy(BIG_ROCK_SPEED * (sin(M_PI / 180.0 * angle)));
        constRotation = -BIG_ROCK_SPIN ;
    }
    else
    {
        point.setX(bottomRight.getX() - 20);
        point.setY(yLocation);
        velocity.setDx(-BIG_ROCK_SPEED * (-cos(M_PI / 180.0 * angle)));
        velocity.setDy(BIG_ROCK_SPEED * (sin(M_PI / 180.0 * angle)));
        constRotation = BIG_ROCK_SPIN ;
    }
    radius = BIG_ROCK_SIZE;
}


void BigRock::draw()
{
   drawLargeAsteroid(point ,angle , constRotation );
}

int BigRock::hit()
{
    kill();
    return BIG_ROCK_POINTS;
}

MediumRock::MediumRock(Point topLeft, Point bottomRight, Point center)
{
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    point = center;
    int rightOrLeft = random(0, 2);
    if(rightOrLeft == 0)
    {
        constRotation = -MEDIUM_ROCK_SPIN;
    }
    else
    {
        constRotation = MEDIUM_ROCK_SPIN;
    }
    radius = MEDIUM_ROCK_SIZE;
}

void MediumRock::draw()
{
   drawMediumAsteroid(point ,angle , constRotation);
}

int MediumRock::hit()
{
    kill();
    return MEDIUM_ROCK_POINTS;
    
}


SmallRock::SmallRock(Point topLeft, Point bottomRight, Point center)
{
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    point = center;
    int rightOrLeft = random(0, 2);
    if(rightOrLeft == 0)
    {
        constRotation = - SMALL_ROCK_SPIN;
    }
    else
    {
        constRotation = SMALL_ROCK_SPIN;
    }
    radius = SMALL_ROCK_SIZE;
}

void SmallRock::draw()
{
    drawSmallAsteroid(point ,angle , constRotation);
}

int SmallRock::hit()
{
   kill();
   return SMALL_ROCK_POINTS;
}
