#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"



// Put your FlyingObject class here
class FlyingObject
{
protected:
    Point point;
    Velocity velocity;
    bool alive;
    //screen dimensions
    Point topLeft;
    Point bottomRight;
    int angle;
    int radius;
    
public:
    FlyingObject();
    ~FlyingObject();
    void setAlive(bool alive);
    void setPoint(Point p);
    void setVelocity(Velocity v);
    void setTopLeft(Point tl);
    void setBottomRight(Point br);
    Point getPoint();
    Velocity getVelocity();
    void setDy(float Dy);
    void setDx(float Dx);
    float getDy();
    float getDx();
    int getRadius();
    bool isAlive();
    void advance();
    virtual void draw();
    void kill();
    virtual int hit(){ return 0; };

};



#endif /* flyingObject_h */
