#include "bullet.h"
#include "point.h"
#include "uiDraw.h"
#include <cmath>




// Put your bullet methods here
Bullet::Bullet()
{
    radius = 2;
    life = 80;
}

void Bullet::draw()
{
   drawDot(point);
   --life;
   isBulletAlive();
}

void Bullet::fire(Point p, int angle)
{
    point.setX(p.getX());
    point.setY(p.getY());
    velocity.setDx(-BULLET_SPEED * (-cos(M_PI / 180.0 * angle)));
    velocity.setDy(BULLET_SPEED * (sin(M_PI / 180.0 * angle)));
}

void Bullet::isBulletAlive()
{
    if(life <= 0)
    {
        kill();
    }
}

