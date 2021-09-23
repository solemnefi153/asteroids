#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 20
#define MEDIUM_ROCK_SIZE 12
#define SMALL_ROCK_SIZE 8

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define  BIG_ROCK_SPEED 1

#define  BIG_ROCK_POINTS 1
#define  MEDIUM_ROCK_POINTS 2
#define  SMALL_ROCK_POINTS 3

#include "flyingObject.h"


// Define the following classes here:
//   Rock
class Rock: public FlyingObject
{
protected:
    int constRotation;
    
public:
    Rock();
    void setConstRotation(int rotation);
};

//   BigRock
class BigRock: public Rock
{
private:
public:
    BigRock(Point topLeft, Point bottomRight);
    void draw();
    int hit();
};


//   MediumRock
class MediumRock: public Rock
{
private:
public:
    MediumRock(Point topLeft, Point bottomRight, Point center);
    void draw();
    int hit();
};


//   SmallRock
class SmallRock: public Rock
{
private:
public:
    SmallRock(Point topLeft, Point bottomRight, Point center);
    void draw();
    int hit();
};


#endif /* rocks_h */
