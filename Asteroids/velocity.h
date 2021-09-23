#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project
#include <stdio.h>

class Velocity
{
private:
    float Dx;
    float Dy;
    
public:
    Velocity(float Dx, float Dy);
    Velocity();
    ~Velocity();
    void setDy(float Dy);
    void setDx(float Dx);
    float getDy();
    float getDx();    
};



#endif /* velocity_h */
