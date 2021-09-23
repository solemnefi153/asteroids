#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 8
#define THRUST_AMOUNT 0.1

#include "flyingObject.h"

// Put your Ship class here
class Ship: public FlyingObject
{
private:
    int rotation;
    bool thrust;
public:
    Ship();
    void turnLeft();
    void turnRight();
    void applyThrust();
    void draw();
    int getAngle();
    void setAngle(int angle);
};

#endif /* ship_h */
