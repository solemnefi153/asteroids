#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 10
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "point.h"


// Put your Bullet class here
class Bullet : public FlyingObject
{
private:
    int life;
    
private:
    void isBulletAlive();
    
public:
    Bullet();
    void draw();
    void fire(Point p, int angle);
};



#endif /* bullet_h */
