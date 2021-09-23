//
//  star.hpp
//  Asteroids
//
//  Created by Nayade Aguilar on 11/30/19.
//  Copyright © 2019 Nefi Aguilar. All rights reserved.
//

#ifndef star_h
#define star_h

#include "flyingObject.h"
#include "point.h"
#include <stdio.h>

class Star: public FlyingObject
{
private:
public:
    Star();
    void initiateStar(Point tl, Point br);
    void draw();
};
#endif /* star_h */
