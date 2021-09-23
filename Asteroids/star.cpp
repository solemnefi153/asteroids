//
//  star.cpp
//  Asteroids
//
//  Created by Nayade Aguilar on 11/30/19.
//  Copyright © 2019 Nefi Aguilar. All rights reserved.
//

#include "star.h"
#include "uiDraw.h"
#define STAR_RADIUS 20
#define STAR_SPEED 5


Star::Star()
{
    alive = true;
    radius = STAR_RADIUS;
}

void Star::initiateStar(Point tl, Point br)
{
    bottomRight = br;
    topLeft = tl;
    angle = random(1, 360);
    int yLocation = random(br.getY() + 20, tl.getY() - 20);
    int xLocation =  random(tl.getX() + 20, br.getX() - 20);
    point.setX(xLocation);
    point.setY(yLocation);
    velocity.setDx(STAR_SPEED * (-cos(M_PI / 180.0 * angle)));
    velocity.setDy(STAR_SPEED * (sin(M_PI / 180.0 * angle)));
}

void Star::draw()
{
   drawSacredBird(point , radius);
}



